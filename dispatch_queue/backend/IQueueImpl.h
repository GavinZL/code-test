#ifndef IQueueImpl_H
#define IQueueImpl_H

#include "TaskOperator.h"
#include "TaskQueueDefine.h"
#include "IThreadPool.h"
#include <chrono>
#include "QueueDefine.h"
namespace task 
{
class IThreadPool;
class IQueueImpl
{
public:
    IQueueImpl(TaskQueueType type, const ThreadPoolPtr& threadPool):mType(type), mThreadPool(threadPool){}
    virtual ~IQueueImpl() = default;
    inline TaskQueueType type() const
    {
        return mType;
    }

    virtual void async(const TaskOperatorPtr& task) = 0;
    virtual void sync(const TaskOperatorPtr& task) = 0;
    virtual void after(std::chrono::milliseconds delay, const TaskOperatorPtr& task) = 0;

protected:
    inline const ThreadPoolPtr& _threadPool() const
    {
        return mThreadPool;
    }

private:
    TaskQueueType mType;
    ThreadPoolPtr mThreadPool;          //线程池
};

}


#endif // IQueueImpl_H