#include "WorkThread.h"
#include <chrono>
#include <cstdio>
namespace task
{
    // 自旋尝试获取信号量的次数
    static constexpr auto sMaxSpinCount = 10;

    // 线程调度，最大等待时间2分钟还没有任务，可以自动退出 [独占线程除外]
    static constexpr auto sMaxSleepTimeout = std::chrono::seconds(120);

    static int32_t sId() 
    {
        static std::atomic<int32_t> sId { 1 << 16 };
        return sId.fetch_add(1, std::memory_order_relaxed);
    }

    WorkThread::WorkThread(const std::weak_ptr<IThreadPool>& threadPool)
    : mThreadPool(threadPool)
    , mThread(&WorkThread::run, this)
    {
        mId = sId();
        printf("WorkThread::WorkThread, threadId: %d\n", threadId());
    }
    
    WorkThread::~WorkThread()
    {
        printf("WorkThread::~WorkThread, threadId: %d\n", threadId());
        if(mThread.joinable())
        {
            mThread.join();
        }
    }

    void WorkThread::run()
    {
        printf("WorkThread::run, threadId: %d, name: %s\n", std::this_thread::get_id(), mName.c_str());
        while (!mIsCancelled.load(std::memory_order_acquire))
        {
            if(mNameChanged)
            {
                _changeName();
            }

            if(mPriorityChanged)
            {
                _changePriority();
            }

            // 任务执行
            bool ret = true;
            if(mIsExclusive)
            {
                ret = _exclusive();
            }
            else
            {
                ret = _parallel();
            }

            // 如果线程长时间没有任务执行，自动退出线程
            if(!ret)
            {
                break;
            }
        }

        // 线程结束，从线程池中移除, 结束自己 
        auto pool = _getThreadPool();
        if(pool)
        {
            pool->unregisterWorkThread(shared_from_this());
        }

        printf("WorkThread::run, threadId: %d, exit, name: %s\n", std::this_thread::get_id(), mName.c_str());
    }

    void WorkThread::cancel()
    {
        mIsCancelled.store(true, std::memory_order_release);
    }

    bool WorkThread::commit(const TaskOperatorPtr& task)
    {
        bool ret = mOps.enqueue(task);
        mSemaphore.release();
        return ret;
    }

    bool WorkThread::commit(TaskOperatorPtr&& task) noexcept
    {
        bool ret = mOps.enqueue(std::move(task));
        mSemaphore.release();
        return ret;
    }

    std::shared_ptr<IThreadPool> WorkThread::_getThreadPool()
    {
        if(!mThreadPool.expired())
        {
            return mThreadPool.lock();
        }
        return nullptr;
    }

    bool WorkThread::_exclusive()
    {
        // 等待信号量 或 超时
        bool flag = mSemaphore.waitAcquire(sMaxSleepTimeout);

        // 超时结束 & 当前线程没有被attach，可以自己退出
        if(!flag && !mIsExclusive)
        {
            return false;
        }

        // 执行任务
        TaskOperatorPtr op;
        if(mOps.try_dequeue(op) && op)
        {
            mIsRunning = true;
            printf("WorkThread::_exclusive, threadId: %d\n", threadId());
            (*op)();
            mIsRunning = false;
        }

        return true;
    }

    bool WorkThread::_parallel()
    {
        auto& data = _getThreadPool()->getData();

         // 整个线程池数据，第一次尝试获取信号量【无锁】
         bool flag = data->mSemaphore.tryAcquire();
         if(!flag)
         {
             // 自旋尝试10次
             flag = data->mSemaphore.spinAcquire(sMaxSpinCount);
         }
         if(!flag)
         {
            // 等待信号量 或 超时
            // 认为线程处于wait状态，线程池空闲线程+1(所有线程同步看见 memory_order_seq_cst)
            data->mIdleThreads.fetch_add(1, std::memory_order_seq_cst);
            flag = data->mSemaphore.waitAcquire(sMaxSleepTimeout);
            // 等到信号量，线程池空闲线程-1 或者 超时了，线程池空闲线程-1
            data->mIdleThreads.fetch_sub(1, std::memory_order_release);
            if(!flag)
            {
                // 超时了，尝试再获取一次信号量
                if(!data->mSemaphore.tryAcquire())
                {
                    // 失败了，表示线程需要退出了
                    data->mActiveThreads.fetch_sub(1, std::memory_order_release);
                    return false;       // 线程退出了
                }
            }
         }

        // 从高到低优先级 进行任务执行
        TaskOperatorPtr op;
        for(int i=0; i<(int)TaskQueuePriority::TQP_Count; ++i)
        {
            if(data->mTaskQueues[i].try_dequeue(op) && op)
            {
                break;
            }
        }

        if(op)
        {
            mIsRunning = true;
            printf("WorkThread::_parallel, threadId: %d\n", threadId());
            (*op)();
            mIsRunning = false;
        }

        return true;
    }

    void WorkThread::_changeName()
    {
    #ifdef __APPLE__
        pthread_setname_np(mName.c_str());
    #elif __ANDROID__
        pthread_setname_np(mThread.native_handle(), mName.c_str());
    #endif
    }

    void WorkThread::_changePriority()
    {
    #ifdef __ANDROID__
        int pri = 0;
        switch (mPriority)
        {
            case ThreadPriority::TP_LOW:
                pri = 10;
                break;
            case ThreadPriority::TP_NORMAL:
                pri = 0;
                break;
            case ThreadPriority::TP_HIGH:
                pri = -19;
                break;
            default:
                LOGE("[HY]unknown thread priority");
        }
        // int nice(int inc);  //  adds inc to the nice value for the calling thread
        int old = nice(0);
        int ret = nice(pri - old);
        if (-1 == ret)
        {
            LOGE("[HY]failed to set nice(%d), pri", ret);
        }
    #else
        int                max  = sched_get_priority_max(SCHED_FIFO);
        int                min  = sched_get_priority_min(SCHED_FIFO);
        int                half = min + (max - min) / 2;
        struct sched_param sp;
        switch (mPriority)
        {
            case task::WorkThreadPriority::WTP_Low:
                sp.sched_priority = min;
                break;
            case task::WorkThreadPriority::WTP_High:
                sp.sched_priority = max;
                break;
            default:
                sp.sched_priority = half;
                break;
        }
        int error = pthread_setschedparam(mThread.native_handle(), SCHED_FIFO, &sp);
        if (error != 0)
        {
            // LOGE("[HY]failed to set thread priority error: %d", error);
        }
    #endif
    }

}