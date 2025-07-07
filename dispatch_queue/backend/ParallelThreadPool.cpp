#include "ParallelThreadPool.h"
#include "QueueDefine.h"
#include "WorkThread.h"
#include <atomic>
#include <cassert>
#include <cstdint>
#include <memory>
#include <mutex>
#include "SysUtils.h"

namespace queue
{

    ParallelThreadPool::ParallelThreadPool()
    {
        // 线程池最大线程数为cpu核数
        mData = std::make_shared<Data>();
        mData->mMaxThreads.store(SysUtils::cpuCount(), std::memory_order_release);
    }

    ParallelThreadPool::~ParallelThreadPool()
    {
        // 通知所有线程退出
        mData->mSemaphore.release(mData->mMaxThreads.load(std::memory_order_acquire));
    }

    void ParallelThreadPool::registerWorkThread(const std::shared_ptr<WorkThread>& thread)
    {
        std::lock_guard<std::mutex> lock(mParallelMutex);
        mParallelThreads[thread->threadId()] = thread;
    }

    void ParallelThreadPool::unregisterWorkThread(const std::shared_ptr<WorkThread>& thread)
    {
        std::lock_guard<std::mutex> lock(mParallelMutex);
        mParallelThreads.erase(thread->threadId());
    }

    void ParallelThreadPool::execute(const TaskOperatorPtr& task, TaskQueuePriority priority)
    {
        // 优先级判断
        if(priority < TaskQueuePriority::TQP_Low || priority >= TaskQueuePriority::TQP_Count)
        {
            assert(false);
            return;
        }

        int32_t prio = static_cast<int32_t>(priority);
        const auto enqueued = mData->mTaskQueues[prio].enqueue(task);
        if(enqueued)
        {
            // 信号量唤醒线程
            mData->mSemaphore.release();
        }

        // 线程调度
        _schedule();
    }

    void ParallelThreadPool::_schedule()
    {
        // 如果有idle线程，不需要调度
        const auto idleCount = mData->mIdleThreads.load(std::memory_order_acquire);
        if(idleCount > 0)
        {
            return;
        }

        // 是否需要创建新线程
        const auto activeCount = mData->mActiveThreads.load(std::memory_order_acquire);
        if(activeCount < mData->mMaxThreads.load(std::memory_order_acquire))
        {
            // 创建新线程，注册到线程池
            auto thread = std::make_shared<WorkThread>(shared_from_this());
            registerWorkThread(thread);
        }
        // 如果达到最大线程数量，就只有等待被调度了
        // ...
    }
}