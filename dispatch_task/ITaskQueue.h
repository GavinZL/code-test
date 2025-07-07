//任务队列基类

#pragma once

#include "Task.h"
#include <utility>
#include <memory>
namespace task
{

class ITaskQueue
{
public:
    ITaskQueue()          = default;
    virtual ~ITaskQueue() = default;

public:
    virtual void     push(std::shared_ptr<Task> task)    = 0;
    virtual bool     tryPop(std::shared_ptr<Task>& task) = 0;
    virtual void     clear()                             = 0;
    virtual uint32_t size()                              = 0;
    virtual bool     empty()                             = 0;
};

}  // namespace task
