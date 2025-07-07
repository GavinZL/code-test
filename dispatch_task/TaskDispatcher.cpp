
#include "TaskDispatcher.hpp"
#include "UnsortedQueue.hpp"
#include <iostream>
namespace task
{

void TaskDispatcher::initalize(uint32_t threadCnt)
{
    _threadPool.reset(new TaskThreadPool());
    _threadPool->initialize(threadCnt);
}

void TaskDispatcher::destroy()
{
    _threadPool->destory();
}

void TaskDispatcher::pause()
{
    _threadPool->pause();
}

void TaskDispatcher::resume()
{
    _threadPool->resume();
}

uint16_t TaskDispatcher::getThreadCount() const
{
    return _threadPool->getThreadCnt();
}

void TaskDispatcher::setFixThread(uint32_t index, bool fix)
{
    _threadPool->setFixThread(index, fix);
}

void TaskDispatcher::dispatchTask(std::shared_ptr<Task>& task)
{
    //1. 判断task是同步 or 异步
    if (task->getTaskRunType() == task::TaskRunType::TT_SYNCHRONOUS)
    {
        task->doTask();
        return;
    }

    //2. 判断task是否固定线程执行
    auto threadId = task->getThreadId();
    if (threadId != -1)
    {
        if (threadId >= 0 && threadId < getThreadCount())
        {
            const auto& thread = _threadPool->getThreadByIndex(threadId);
            if (thread)
            {
                thread->commitTask(task);
                return;
            }
        }
    }

    //3. 随机
    const auto& thread = _threadPool->getThread();
    if (thread)
    {
        thread->commitTask(task);
    }
}

}  // namespace task
