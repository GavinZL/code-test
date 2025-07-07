#include "TaskThread.hpp"
#include "UnsortedQueue.hpp"

#include <iostream>
#include <chrono>

namespace task
{

void TaskThread::start()
{
    _needStop = false;
    _taskQueue.reset(new UnsortedQueue);
    _thread = std::thread(&TaskThread::_run, this);
}

void TaskThread::stop()
{
    _needStop = true;
    _cond_var.notify_one();
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void TaskThread::pause()
{
    _isPause = true;
}

void TaskThread::resume()
{
    _isPause = false;
}

bool TaskThread::isSelfThread()
{
    return std::this_thread::get_id() == _thread.get_id();
}

uint32_t TaskThread::getTaskCnt()
{
    return _taskQueue->size();
}

void TaskThread::commitTask(std::shared_ptr<Task>& task)
{
    //如果调用者为自身线程，直接执行
    if (isSelfThread())
    {
        task->doTask();
        return;
    }

    _taskQueue->push(task);
    _cond_var.notify_one();
}

void TaskThread::_run()
{
    std::cout << "_run begin" << std::endl;
    while (true)
    {
        if (_needStop)
        {
            break;
        }

        if (_isPause)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // 获取一个待执行的 task
        std::shared_ptr<task::Task> task;
        bool                        ret = false;
        {
            // unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
            std::unique_lock<std::mutex> lock{ _mutex };
            _cond_var.wait(lock, [this] {
                return _needStop || !_taskQueue->empty();
            });
            if (_needStop)
            {
                break;
            }
            ret = _taskQueue->tryPop(task);
        }

        //执行任务
        if (ret && task)
        {
            task->doTask();
        }
    }
    std::cout << "_run end" << std::endl;
}

}  // namespace task
