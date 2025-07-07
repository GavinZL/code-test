#include "ExclusiveThreadPool.h"
#include "WorkThread.h"
#include "SysUtils.h"
namespace queue 
{
    void ExclusiveThreadPool::registerWorkThread(const std::shared_ptr<WorkThread>& thread)
    {
        task::WriteLock lock(mExclusiveThreadsLock);
        mExclusiveThreads[thread->threadId()] = thread;
    }

    void ExclusiveThreadPool::unregisterWorkThread(const std::shared_ptr<WorkThread>& thread)
    {
        task::WriteLock lock(mExclusiveThreadsLock);
        mExclusiveThreads.erase(thread->threadId());
    }

    int32_t ExclusiveThreadPool::attachOneThread(const std::string& name, WorkThreadPriority prio)
    {
        int32_t index = -1;
        {
            task::ReadLock lock(mExclusiveThreadsLock);
            for(auto& item : mExclusiveThreads)
            {
                // 没有被占用
                if(item.second && !item.second->isExclusive())
                {
                    item.second->setExclusive(true);
                    item.second->setName(name);
                    item.second->setPriority(prio);
                    index = item.second->threadId();
                    break;
                }
            }
        }

        if(index == -1)
        {
            task::WriteLock lock(mExclusiveThreadsLock);
            // 已经达到最大线程数量限制
            if(mExclusiveThreads.size() >= 2 * SysUtils::cpuCount())
            {
                assert(false);
            }

            // 没有找到合适的线程，创建新线程
            auto thread = std::make_shared<WorkThread>(shared_from_this());
            thread->setExclusive(true);
            thread->setPriority(prio);
            thread->setName(name);
            index = thread->threadId();
            mExclusiveThreads[index] = thread;
        }

        return index;
    }

    void ExclusiveThreadPool::detachOneThread(int32_t threadID)
    {
        task::WriteLock lock(mExclusiveThreadsLock);
        auto it = mExclusiveThreads.find(threadID);
        if(it != mExclusiveThreads.end())
        {
            it->second->setExclusive(false);
        }
    }

    void ExclusiveThreadPool::execute(const TaskOperatorPtr& task, int32_t threadId)
    {
        task::ReadLock lock(mExclusiveThreadsLock);
        auto it = mExclusiveThreads.find(threadId);
        if(it != mExclusiveThreads.end())
        {
            it->second->commit(task);
        }
    }

}