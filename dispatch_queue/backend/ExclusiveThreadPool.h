#ifndef EXCLUSIVE_THREAD_POOL_H
#define EXCLUSIVE_THREAD_POOL_H

#include "IThreadPool.h"
#include <memory>
#include <mutex>
#include <unordered_map>
#include "TaskQueueDefine.h"
#include "3rdparty/ThreadRWLock.hpp"
namespace queue 
{
    class ExclusiveThreadPool : public IThreadPool
    {
    public:
        explicit ExclusiveThreadPool()
        :mExclusiveThreadsLock(task::ThreadRWLock::create()){}
        virtual void registerWorkThread(const std::shared_ptr<WorkThread>& thread) override;
        virtual void unregisterWorkThread(const std::shared_ptr<WorkThread>& thread) override;

        virtual void execute(const TaskOperatorPtr& task, int32_t threadId) override;

        // 获取对应优先级的独占线程
        virtual int32_t attachOneThread(const std::string& name,  WorkThreadPriority priority = WorkThreadPriority::WTP_Normal) override;
        virtual void detachOneThread(int32_t threadID) override;

    private:
        // 独占线程集合
        std::shared_ptr<task::ThreadRWLock> mExclusiveThreadsLock;
        std::unordered_map<int32_t, std::shared_ptr<WorkThread>> mExclusiveThreads;
    };

}


#endif // EXCLUSIVE_THREAD_POOL_H