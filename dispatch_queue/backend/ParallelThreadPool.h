#ifndef __TaskThreadPool_H__
#define __TaskThreadPool_H__


#include "IThreadPool.h"
#include "Semaphore.h"
#include <array>
#include <atomic>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "QueueDefine.h"
namespace queue
{
class WorkThread;
class ParallelThreadPool: public IThreadPool
{
public:
    explicit ParallelThreadPool();
    ~ParallelThreadPool();

    // 线程池管理线程生命周期 
    virtual void registerWorkThread(const std::shared_ptr<WorkThread>& thread) override;
    virtual void unregisterWorkThread(const std::shared_ptr<WorkThread>& thread) override;

    // 线程池管理任务
    virtual void execute(const TaskOperatorPtr& task, TaskQueuePriority priority = TaskQueuePriority::TQP_Normal) override;

    virtual const std::shared_ptr<Data> getData() const override
    {
        return mData; 
    }

protected:
    // 线程调度
    void _schedule();

private:
    // 并行线程集合
    std::shared_ptr<Data> mData;
    std::mutex mParallelMutex;
    std::unordered_map<int32_t, std::shared_ptr<WorkThread>> mParallelThreads;
};

}


#endif // __TaskThreadPool_H__