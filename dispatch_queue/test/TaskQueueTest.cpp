// #include "gtest/gtest.h"
// #include "gmock/gmock.h"
// #include <memory>
// #include <chrono>
// #include <thread>
// #include <mutex>
// #include "TaskQueue.h"
// #include "TaskGroup.h"
// #include "TaskQueueFactory.h"

// using namespace std;
// using namespace testing;
// using namespace queue;

// class TaskQueueTest : public ::testing::Test {
// protected:
//     void SetUp() override {
//         // 在每个测试用例开始前执行
//     }

//     void TearDown() override {
//         // 在每个测试用例结束后执行
//     }
// };

// // 测试创建串行队列
// TEST_F(TaskQueueTest, CreateSerialQueue) {
//     auto queue = TaskQueueFactory::GetInstance().createSerialTaskQueue("test_serial", WorkThreadPriority::WTP_Normal, false);
//     ASSERT_NE(queue, nullptr);
//     EXPECT_EQ(queue->label(), "test_serial");
// }

// // 测试创建并行队列
// TEST_F(TaskQueueTest, CreateParallelQueue) {
//     auto queue = TaskQueueFactory::GetInstance().createParallelTaskQueue("test_parallel", TaskQueuePriority::TQP_Normal);  
//     ASSERT_NE(queue, nullptr);
//     EXPECT_EQ(queue->label(), "test_parallel");
// }

// // 测试任务执行
// TEST_F(TaskQueueTest, ExecuteTask) {
//     auto queue = TaskQueueFactory::GetInstance().createSerialTaskQueue("test_execute", WorkThreadPriority::WTP_Normal, true);
//     ASSERT_NE(queue, nullptr);

//     bool taskExecuted = false;
//     queue->async([&taskExecuted]() {
//         taskExecuted = true;
//     });

//     // 等待任务执行完成
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     EXPECT_TRUE(taskExecuted);
// }

// // 测试任务组
// TEST_F(TaskQueueTest, TaskGroup) {
//     auto group = TaskQueueFactory::GetInstance().createTaskGroup();
//     ASSERT_NE(group, nullptr);

//     int counter = 0;
//     std::mutex mutex;

//     // 添加多个任务到组
//     for (int i = 0; i < 5; ++i) {
//         group->async([&counter, &mutex]() {
//             std::lock_guard<std::mutex> lock(mutex);
//             counter++;
//         });
//     }

//     // 等待组内所有任务完成
//     group->wait();
//     EXPECT_EQ(counter, 5);
// }