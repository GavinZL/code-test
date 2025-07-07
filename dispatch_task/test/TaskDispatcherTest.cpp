
#include "../TaskDispatcher.hpp"

#include <mutex>
#include <iostream>

//clang++ -std=c++17 -I.. ../TaskThread.cpp ../TaskThreadPool.cpp ../TaskDispatcher.cpp TaskDispatcherTest.cpp -o t

std::mutex g_mutex;

class TestTask : public task::Task
{
public:
    virtual bool _doTask() override
    {
        std::lock_guard<std::mutex> loc(g_mutex);
        std::cout << "task:"<< getTaskId() << ", thread_id: " << std::this_thread::get_id() << "\n";
        return true;
    }
};

int main(int argc, char* argv[])
{

    task::TaskDispatcher dispatcher;

    //两条线程
    dispatcher.initalize(3);

    std::shared_ptr<task::Task> task;
    //1. 固定一条线程，两条随机线程
    // dispatcher.setFixThread(0, true);
    // for(int i=0; i<100; ++i)
    // {
    //     task.reset(new TestTask());
    //     task->setTaskId(i);
    //     if(i % 5 == 0)
    //     {
    //         task->setThreadId(0);
    //     }
    //     dispatcher.dispatchTask(task);
    // }

    //2. 测试future task之间同步操作
    for(int i=0; i<100; ++i)
    {
        task.reset(new TestTask());
        task->setTaskId(i+1);

        {//表示同步执行完成
            std::future fut = task->getSyncFlag();
            dispatcher.dispatchTask(task);
            fut.get();
        }
    }

    // dispatcher.destroy();

    std::this_thread::sleep_for(std::chrono::seconds(30));
    return 0;
}