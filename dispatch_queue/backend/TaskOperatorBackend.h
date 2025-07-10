// 操作基类
#ifndef __HEOPERATION_H__
#define __HEOPERATION_H__

#include <memory>
#include <chrono>
#include <thread>
#include "TaskOperator.h"
#include "TaskQueueDefine.h"
#include "LWBarrier.h"
#include "Consumable.h"
namespace queue
{
    // 处理同步任务
    class TaskBarrierOperator : public TaskOperator
    {
    public:
        explicit TaskBarrierOperator(const TaskOperatorPtr& op) : mRealTask(op)
        {
        }
        ~TaskBarrierOperator() = default;

        virtual void operator()() override
        {
            if(mRealTask)
            {
                (*mRealTask)();
            }
            mBarrier.notify();
        }

        void wait(std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
        {
            mBarrier.wait(timeout);
        }

    private:
        TaskOperatorPtr mRealTask;
        LWBarrier       mBarrier;
    };


    // 延时任务
    class TaskDelayOperator : public TaskOperator
    {
    public:
        TaskDelayOperator(std::chrono::milliseconds delay, const TaskOperatorPtr& op)
            : mDelay(delay)
            , mRealTask(op)
        {
        }
        ~TaskDelayOperator() = default;

        // 执行延时任务是，是休眠了一条线程
        // 此处可以考虑修改线程池中的max threads 或 idle threads， 来达到实时性要求
        // 目前我们场景暂不需要如此实时性
        virtual void operator()() override
        {
            std::this_thread::sleep_for(mDelay);
            if(mRealTask)
            {
                (*mRealTask)();
            }
        }

    private:
        std::chrono::milliseconds mDelay;
        TaskOperatorPtr mRealTask;
    };

    // consumable 操作对象
    class ConsumableOperator : public TaskOperator
    {
    public:
        ConsumableOperator(const TaskOperatorPtr& op, const ConsumablePtr& consumable)
            : mRealTask(op)
            , mConsumable(consumable)
        {
        }
        ~ConsumableOperator() = default;
        
        virtual void operator()() override
        {
            if(mRealTask)
            {
                (*mRealTask)();
            }
            // 释放资源
            if(mConsumable)
            {
                mConsumable->release();
            }
        }

    private:
        ConsumablePtr   mConsumable;
        TaskOperatorPtr mRealTask;
    };

}
#endif // __HEOPERATION_H__
