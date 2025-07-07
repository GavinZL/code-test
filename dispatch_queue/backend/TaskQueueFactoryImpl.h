#ifndef __TASK_QUEUE_FACTORY_IMPL_H__
#define __TASK_QUEUE_FACTORY_IMPL_H__

#include "TaskQueueDefine.h"
#include "TaskQueue.h"
namespace queue
{
    
    class TaskQueueFactoryImpl
    {
    public:
        // 创建串行队列
        TaskQueuePtr createSerialQueue(const std::string& label, WorkThreadPriority priority, bool isExclusive);

        // 创建并行队列
        TaskQueuePtr createParallelQueue(const std::string& label, TaskQueuePriority priority);

        // 获取队列 【全局初始化并行队列】
        TaskQueuePtr& getParallelQueue(TaskQueuePriority priority);
        TaskQueuePtr& getSerialQueue();    
        
        TaskGroupPtr createTaskGroup();
    };

}

#endif