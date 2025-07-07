
#include "TaskQueueFactory.h"
#include "backend/TaskQueueFactoryImpl.h"
#include <memory>
#include <mutex>
namespace queue 
{
    const std::shared_ptr<class TaskQueueFactoryImpl>& TaskQueueFactory::_getFactoryImpl()
    {
        static std::once_flag sFlag;
        std::call_once(sFlag, [this]() {
            mFactoryImpl = std::make_shared<TaskQueueFactoryImpl>();
        });

        return mFactoryImpl;
    }

    TaskQueuePtr TaskQueueFactory::createSerialTaskQueue(const std::string& label, WorkThreadPriority priority, bool isExclusive)
    {
        return _getFactoryImpl()->createSerialQueue(label, priority, isExclusive);
    }

    TaskQueuePtr TaskQueueFactory::createParallelTaskQueue(const std::string& label, TaskQueuePriority priority)
    {
        return _getFactoryImpl()->createParallelQueue(label, priority);
    }

    TaskQueuePtr& TaskQueueFactory::globalParallelQueue(TaskQueuePriority priority)
    {
        return _getFactoryImpl()->getParallelQueue(priority);
    }

    TaskQueuePtr& TaskQueueFactory::globalSerialQueue()
    {
        return _getFactoryImpl()->getSerialQueue();
    }

    TaskGroupPtr TaskQueueFactory::createTaskGroup()
    {
        return _getFactoryImpl()->createTaskGroup();
    }

}