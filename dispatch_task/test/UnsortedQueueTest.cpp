
#include "../UnsortedQueue.hpp"
#include "../Task.h"
#include <cstdio>
#include <utility>
#include <memory>

class TestTask : public task::Task
{
public:
    TestTask(int i) : index(i){}

    virtual bool _doTask() override
    {
        printf("index: %d\n", index);
        return true;
    }

private:
    int index = 0;
};


int main(int argc, char* argv[])
{
    task::UnsortedQueue queue;
    queue.push(std::make_shared<TestTask>(1));
    queue.push(std::make_shared<TestTask>(2));
    queue.push(std::make_shared<TestTask>(3));

    std::shared_ptr<task::ITask> task;

    queue.tryPop(task);
    task->doTask();

    queue.tryPop(task);
    task->doTask();

    queue.tryPop(task);
    task->doTask();

    return 0;
}