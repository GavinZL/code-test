#include "ParallelQueueImpl.h"
#include "TaskOperatorBackend.h"
#include <cassert>
namespace queue 
{

    ParallelQueueImpl::ParallelQueueImpl(TaskQueuePriority prio, const ThreadPoolPtr& threadPool)
    : IQueueImpl(TaskQueueType::TQT_Parallel, threadPool)
    , mPriority(prio)
    {
    }

    ParallelQueueImpl::~ParallelQueueImpl()
    {
    }

    void ParallelQueueImpl::async(const TaskOperatorPtr& task)
    {
        assert(_threadPool());
        _threadPool()->execute(task, mPriority);
    }

    void ParallelQueueImpl::sync(const TaskOperatorPtr& task)
    {
        assert(_threadPool());
        auto syncTask = std::make_shared<TaskBarrierOperator>(task);
        _threadPool()->execute(syncTask, mPriority);
        syncTask->wait();
    }

    void ParallelQueueImpl::after(std::chrono::milliseconds delay, const TaskOperatorPtr& task)
    {
        assert(_threadPool());
        auto delayTask = std::make_shared<TaskDelayOperator>(delay, task);
        _threadPool()->execute(delayTask, mPriority);
    }

}