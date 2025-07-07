#include "SerialQueueImpl.h"

#include "LWBarrier.h"
#include "TaskOperatorBackend.h"
#include <cassert>
#include <memory>
namespace queue 
{
    SerialQueueImpl::SerialQueueImpl(const std::string& label, 
        bool isExclusive, 
        const ThreadPoolPtr& threadPool, 
        WorkThreadPriority prio)
    : IQueueImpl(TaskQueueType::TQT_Serial, threadPool)
    , mIsExclusive(isExclusive)
    {
        if(mIsExclusive)
        {
            mThreadId = _threadPool()->attachOneThread(label, prio);
        }
    }

    SerialQueueImpl::~SerialQueueImpl()
    {
        if(mIsExclusive && mThreadId >= 0)
        {
            _threadPool()->detachOneThread(mThreadId);
        }
    }

    void SerialQueueImpl::async(const TaskOperatorPtr& task)
    {
        assert(_threadPool());
        if(mIsExclusive)
        {
            _threadPool()->execute(task, mThreadId);
        }else {
            _threadPool()->execute(task);
        }
    }

    void SerialQueueImpl::sync(const TaskOperatorPtr& task)
    {
        assert(_threadPool());
        // 转为一个 BarrierTaskOperator
        auto syncTask = std::make_shared<TaskBarrierOperator>(task);
        if(mIsExclusive)
        {
            _threadPool()->execute(syncTask, mThreadId);
        }else {
            _threadPool()->execute(syncTask);
        }
        syncTask->wait();
    }

    void SerialQueueImpl::after(std::chrono::milliseconds delay, const TaskOperatorPtr& task)
    {
        assert(_threadPool());
        auto delayTask = std::make_shared<TaskDelayOperator>(delay, task);
        if(mIsExclusive){
            _threadPool()->execute(delayTask, mThreadId);
        }else {
            _threadPool()->execute(delayTask);
        }
    }
}