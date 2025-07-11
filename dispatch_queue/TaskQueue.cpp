#include "TaskQueue.h"
#include "TaskOperator.h"
#include "backend/IQueueImpl.h"

namespace task
{
    TaskQueue::TaskQueue(const std::string& label, const TaskQueueImplPtr& impl)
    : mLabel(label)
    , mImpl(impl)
    {}

    void TaskQueue::async(const TaskOperatorPtr& task)
    {
        mImpl->async(task);
    }

    void TaskQueue::sync(const TaskOperatorPtr& task)
    {
        mImpl->sync(task);
    }

    void TaskQueue::after(std::chrono::milliseconds delay, const TaskOperatorPtr& task)
    {
        mImpl->after(delay, task);
    }
}
