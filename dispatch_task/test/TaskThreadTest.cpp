
#include "../TaskThread.hpp"
#include "../Task.h"
#include <chrono>
#include <cstdio>

//clang++ -std=c++17 -I.. TaskThreadTest.cpp ../TaskThread.cpp -o t

class TestTask : public task::Task
{
public:
    virtual bool _doTask() override
    {
        std::cout << "test-task, thread_id: " << std::this_thread::get_id() << "\n";
        return true;
    }
};

///////////////////////////////////////
int main(int argc, char *argv[])
{
    task::TaskThread thread;
    thread.start();

    std::shared_ptr<task::Task> task = std::make_shared<TestTask>();

    thread.commitTask(task);

    std::cout << "main: " << std::this_thread::get_id() << "\n";

    thread.stop();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}