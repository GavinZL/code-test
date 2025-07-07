
#pragma once

#include "Task.h"
#include "TaskThreadPool.hpp"

namespace task
{

class TaskDispatcher
{
public:
    void initalize(uint32_t threadCnt = 1);
    void destroy();

    void pause();
    void resume();

    uint16_t getThreadCount() const;
    void     setFixThread(uint32_t index, bool fix);

    void dispatchTask(std::shared_ptr<Task>& task);

private:
    std::unique_ptr<TaskThreadPool> _threadPool;
};

}  // namespace task
