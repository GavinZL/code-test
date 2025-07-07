// 串行队列实现
#ifndef __SERIAL_TASK_QUEUE_IMPL_H__
#define __SERIAL_TASK_QUEUE_IMPL_H__

#include "IQueueImpl.h"
namespace queue 
{
    class SerialQueueImpl : public IQueueImpl
    {
    public:
        SerialQueueImpl(const std::string& label, bool isExclusive, const ThreadPoolPtr& threadPool, WorkThreadPriority prio);
        ~SerialQueueImpl();

        virtual void async(const TaskOperatorPtr& task) override;
        virtual void sync(const TaskOperatorPtr& task) override;
        virtual void after(std::chrono::milliseconds delay, const TaskOperatorPtr& task) override;

    private:
        bool    mIsExclusive {false};
        int32_t mThreadId {-1};
    };

}



#endif // __SERIAL_TASK_QUEUE_IMPL_H__