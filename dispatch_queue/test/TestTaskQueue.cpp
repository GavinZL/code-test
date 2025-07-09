

#include "../TaskQueue.h"
#include "../TaskQueueFactory.h"
#include "../TaskGroup.h"
#include <cassert>
#include <chrono>
#include <cstdio>
#include <stdio.h>
#include <thread>
using namespace queue;
// clang++ -o test TestTaskQueue.cpp -L../build/lib -ldispatch_queue -Wl,-rpath,@loader_path/../build/lib -g -O0

int main(int argc, char* argv[])
{
    // 独占线程
    // printf("-------------------------------------- 独占线程 --------------------------------------\n");
    // auto queue = TaskQueueFactory::GetInstance().createSerialTaskQueue("test_execute", WorkThreadPriority::WTP_Normal, true);
    // assert(queue != nullptr);
    // queue->async([]() {
    //     printf("test_execute 1: thread_id: %d\n", std::this_thread::get_id());
    // });

    // queue->async([]() {
    //     printf("test_execute 2: thread_id: %d\n", std::this_thread::get_id());  
    // });

    // queue->async([]() {
    //     printf("test_execute 3: thread_id: %d\n", std::this_thread::get_id());  
    // });


    // 共享线程
    // printf("-------------------------------------- 共享线程 --------------------------------------\n");
    // auto queue2 = TaskQueueFactory::GetInstance().createSerialTaskQueue("test_execute2", WorkThreadPriority::WTP_Normal, false);
    // assert(queue2 != nullptr);
    // queue2->async([]() {
    //     printf("test_execute 4: thread_id: %d\n", std::this_thread::get_id());
    // });
    // queue2->async([]() {
    //     printf("test_execute 5: thread_id: %d\n", std::this_thread::get_id());
    // });

    // 任务组
    // printf("-------------------------------------- 任务组 --------------------------------------\n");
    // auto group = TaskQueueFactory::GetInstance().createTaskGroup();
    // assert(group != nullptr);
    // group->async([]() {
    //     printf("test_execute 6: thread_id: %d\n", std::this_thread::get_id());
    //     std::this_thread::sleep_for(std::chrono::seconds(3));
    // });
    // group->async([]() {
    //     printf("test_execute 7: thread_id: %d\n", std::this_thread::get_id());
    // });

    // printf("wait before...\n");
    // group->wait();

    // printf("wait after...\n");


    // 同步任务
    // printf("-------------------------------------- 同步任务 --------------------------------------\n");
    // auto queue = TaskQueueFactory::GetInstance().globalParallelQueue(TaskQueuePriority::TQP_Normal);
    // queue->sync([]() {
    //     printf("test_execute 8: thread_id: %d\n", std::this_thread::get_id());
    // });
    // queue->sync([]() {
    //     printf("test_execute 9: thread_id: %d\n", std::this_thread::get_id());
    // });
    // queue->sync([]() {
    //     printf("test_execute 10: thread_id: %d\n", std::this_thread::get_id());
    // });

    // printf("-------------sync wait\n");


    // 延时任务
    printf("---------------------------延时任务----------------------------\n");
    auto queue = TaskQueueFactory::GetInstance().globalParallelQueue(TaskQueuePriority::TQP_Normal);
    queue->after(std::chrono::milliseconds(3000), []() {
        printf("test_execute 11: thread_id: %d\n", std::this_thread::get_id());
    });

    printf("delay 3s\n");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    getchar();
    return 0;
}
