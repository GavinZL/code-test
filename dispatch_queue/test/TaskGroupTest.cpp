// #include <gtest/gtest.h>
// #include <gmock/gmock.h>
// #include <memory>
// #include <chrono>
// #include <thread>
// #include <mutex>
// #include <atomic>
// #include <stdexcept>
// #include "TaskGroup.h"
// #include "TaskQueue.h"
// #include "TaskQueueFactory.h"

// using namespace std;
// using namespace testing;

// class TaskGroupTest : public ::testing::Test {
// protected:
//     void SetUp() override {
//         factory = std::make_shared<TaskQueueFactory>();
//         queue = factory->createParallelQueue("test_queue", 4);
//     }

//     void TearDown() override {
//         queue.reset();
//         factory.reset();
//     }

//     std::shared_ptr<TaskQueueFactory> factory;
//     std::shared_ptr<TaskQueue> queue;
// };

// // 测试任务组的基本功能
// TEST_F(TaskGroupTest, BasicGroupOperations) {
//     auto group = queue->createGroup();
//     ASSERT_NE(group, nullptr);

//     std::atomic<int> counter{0};
//     const int taskCount = 5;

//     // 添加多个任务到组
//     for (int i = 0; i < taskCount; ++i) {
//         group->async([&counter]() {
//             counter++;
//             std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         });
//     }

//     // 等待所有任务完成
//     group->wait();
//     EXPECT_EQ(counter, taskCount);
// }

// // 测试任务组的嵌套
// TEST_F(TaskGroupTest, NestedGroups) {
//     auto outerGroup = queue->createGroup();
//     ASSERT_NE(outerGroup, nullptr);

//     std::atomic<int> counter{0};

//     // 外层任务
//     outerGroup->async([&]() {
//         counter++;

//         // 创建内层任务组
//         auto innerGroup = queue->createGroup();
//         ASSERT_NE(innerGroup, nullptr);

//         // 添加内层任务
//         for (int i = 0; i < 3; ++i) {
//             innerGroup->async([&counter]() {
//                 counter++;
//                 std::this_thread::sleep_for(std::chrono::milliseconds(10));
//             });
//         }

//         // 等待内层任务组完成
//         innerGroup->wait();
//     });

//     // 等待外层任务组完成
//     outerGroup->wait();
//     EXPECT_EQ(counter, 4); // 1个外层任务 + 3个内层任务
// }

// // 测试任务组的取消操作
// TEST_F(TaskGroupTest, GroupCancellation) {
//     auto group = queue->createGroup();
//     ASSERT_NE(group, nullptr);

//     std::atomic<int> counter{0};
//     std::atomic<bool> shouldCancel{false};

//     // 添加长时间运行的任务
//     for (int i = 0; i < 5; ++i) {
//         group->async([&counter, &shouldCancel]() {
//             if (!shouldCancel) {
//                 std::this_thread::sleep_for(std::chrono::milliseconds(100));
//                 counter++;
//             }
//         });
//     }

//     // 在任务执行过程中取消
//     std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     shouldCancel = true;
//     group->cancel();

//     // 等待所有任务完成或取消
//     group->wait();
//     EXPECT_LT(counter, 5); // 由于取消操作，完成的任务数应该小于总任务数
// }

// // 测试任务组的异常处理
// TEST_F(TaskGroupTest, GroupExceptionHandling) {
//     auto group = queue->createGroup();
//     ASSERT_NE(group, nullptr);

//     // 添加会抛出异常的任务
//     group->async([]() {
//         throw std::runtime_error("Test exception");
//     });

//     // 等待任务完成，应该不会导致测试崩溃
//     EXPECT_NO_THROW(group->wait());
// }