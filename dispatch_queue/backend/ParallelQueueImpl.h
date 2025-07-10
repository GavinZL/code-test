#ifndef __PARALLEL_TASK_QUEUE_IMPL_H__
#define __PARALLEL_TASK_QUEUE_IMPL_H__

#include "IQueueImpl.h"
namespace task 
{
    class ParallelQueueImpl : public IQueueImpl
    {
    public:
        ParallelQueueImpl(TaskQueuePriority prio, const ThreadPoolPtr& threadPool);
        ~ParallelQueueImpl();

        virtual void async(const TaskOperatorPtr& task) override;
        virtual void sync(const TaskOperatorPtr& task) override;
        virtual void after(std::chrono::milliseconds delay, const TaskOperatorPtr& task) override;

    private:
        TaskQueuePriority   mPriority {TaskQueuePriority::TQP_Normal};
    };

}



#endif // __PARALLEL_TASK_QUEUE_IMPL_H__