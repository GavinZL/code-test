//任务队列线程
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

#include "Task.h"
#include "ITaskQueue.h"

namespace task
{

class TaskThread
{
public:
    void     start();
    void     stop();
    void     pause();
    void     resume();
    bool     isSelfThread();
    uint32_t getTaskCnt();

    void commitTask(std::shared_ptr<Task>& task);

protected:
    void _run();

private:
    std::atomic<bool>           _isPause  = false;  //是否暂停状态
    std::atomic<bool>           _needStop = false;  //是否需要停止
    std::thread                 _thread;
    std::unique_ptr<ITaskQueue> _taskQueue;

    std::mutex              _mutex;
    std::condition_variable _cond_var;

    //字段定义
    DECLARE_VEARIABLE(bool, FixThread, false);
};

}  // namespace task
