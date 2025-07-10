// 工作线程

#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__

#include <atomic>
#include <cstdint>
#include <memory>
#include <thread>
#include <mutex>
#include "QueueDefine.h"
#include "IThreadPool.h"
#include "Semaphore.h"
#include "TaskQueueDefine.h"
namespace task
{
    class WorkThread : public std::enable_shared_from_this<WorkThread>
    {
    public:
        explicit WorkThread(const std::weak_ptr<IThreadPool>& threadPool);
        ~WorkThread();

        // 获取线程ID
        int32_t threadId() const 
        {
            return mId;
        }

        inline void setExclusive(bool isExclusive)
        {
            mIsExclusive = isExclusive;
        }

        inline bool isExclusive() const
        {
            return mIsExclusive;
        }

        inline void setPriority(WorkThreadPriority prio)
        {
            mPriority = prio;
            mPriorityChanged = true;
        }

        inline WorkThreadPriority getPriority() const
        {
            return mPriority;
        }

        inline void setName(const std::string& name)
        {
            mName = name;
            mNameChanged = true;
        }

        inline const std::string& getName() const
        {
            return mName;
        }

        void run();
        void cancel();

        // 提交任务
        bool commit(const TaskOperatorPtr& task);
        bool commit(TaskOperatorPtr&& task) noexcept;

    protected:
        void _changeName();
        void _changePriority();
        std::shared_ptr<IThreadPool> _getThreadPool();

        bool _exclusive();
        bool _parallel();

    private:
        // 线程ID
        int32_t mId { 0 };

        bool mIsExclusive {false};       //是否为独占线程
        bool mPriorityChanged{ false };
        WorkThreadPriority mPriority {WorkThreadPriority::WTP_Normal};

        bool mNameChanged{ false };
        std::string mName;

        //是否取消
        std::atomic<bool> mIsCancelled {false};      
        
        //线程任务队列
        WorkQueue mOps;                              
        std::thread mThread;

        //归属线程池, 弱引用
        std::weak_ptr<IThreadPool>   mThreadPool;    

        // 独占线程通知
        Semaphore mSemaphore;

    };


    using WorkThreadPtr = std::shared_ptr<WorkThread>;
}

#endif // __WORKTHREAD_H__
