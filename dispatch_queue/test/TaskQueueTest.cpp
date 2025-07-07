#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include "TaskQueue.h"
#include "TaskQueueFactory.h"

using namespace std;
using namespace testing;

class TaskQueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例开始前执行
        factory = std::make_shared<TaskQueueFactory>();
    }

    void TearDown() override {
        // 在每个测试用例结束后执行
        factory.reset();
    }

    std::shared_ptr<TaskQueueFactory> factory;
};

// 测试创建串行队列
TEST_F(TaskQueueTest, CreateSerialQueue) {
    auto queue = factory->createSerialQueue("test_serial");
    ASSERT_NE(queue, nullptr);
    EXPECT_EQ(queue->getName(), "test_serial");
}

// 测试创建并行队列
TEST_F(TaskQueueTest, CreateParallelQueue) {
    auto queue = factory->createParallelQueue("test_parallel", 2);
    ASSERT_NE(queue, nullptr);
    EXPECT_EQ(queue->getName(), "test_parallel");
}

// 测试任务执行
TEST_F(TaskQueueTest, ExecuteTask) {
    auto queue = factory->createSerialQueue("test_execute");
    ASSERT_NE(queue, nullptr);

    bool taskExecuted = false;
    queue->async([&taskExecuted]() {
        taskExecuted = true;
    });

    // 等待任务执行完成
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(taskExecuted);
}

// 测试任务组
TEST_F(TaskQueueTest, TaskGroup) {
    auto queue = factory->createParallelQueue("test_group", 2);
    ASSERT_NE(queue, nullptr);

    auto group = queue->createGroup();
    ASSERT_NE(group, nullptr);

    int counter = 0;
    std::mutex mutex;

    // 添加多个任务到组
    for (int i = 0; i < 5; ++i) {
        group->async([&counter, &mutex]() {
            std::lock_guard<std::mutex> lock(mutex);
            counter++;
        });
    }

    // 等待组内所有任务完成
    group->wait();
    EXPECT_EQ(counter, 5);
}