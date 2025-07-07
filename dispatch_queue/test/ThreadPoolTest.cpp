// #include <gtest/gtest.h>
// #include <gmock/gmock.h>
// #include <memory>
// #include <chrono>
// #include <thread>
// #include <mutex>
// #include <atomic>
// #include <future>
// #include <vector>
// #include "backend/ParallelThreadPool.h"
// #include "backend/ExclusiveThreadPool.h"

// using namespace std;
// using namespace testing;

// class ThreadPoolTest : public ::testing::Test {
// protected:
//     void SetUp() override {}
//     void TearDown() override {}
// };

// // 测试并行线程池
// TEST_F(ThreadPoolTest, ParallelThreadPool) {
//     ParallelThreadPool pool(4); // 创建4个线程的线程池
//     pool.start();

//     std::atomic<int> counter{0};
//     std::vector<std::future<void>> futures;

//     // 提交多个任务
//     for (int i = 0; i < 10; ++i) {
//         auto future = pool.commit([&counter]() {
//             counter++;
//             std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         });
//         futures.push_back(std::move(future));
//     }

//     // 等待所有任务完成
//     for (auto& future : futures) {
//         future.wait();
//     }

//     EXPECT_EQ(counter, 10);
//     pool.stop();
// }

// // 测试独占线程池
// TEST_F(ThreadPoolTest, ExclusiveThreadPool) {
//     ExclusiveThreadPool pool;
//     pool.start();

//     std::atomic<int> counter{0};
//     std::atomic<std::thread::id> taskThreadId;

//     // 提交多个任务，确保它们在同一个线程中执行
//     for (int i = 0; i < 5; ++i) {
//         pool.commit([&counter, &taskThreadId]() {
//             if (counter == 0) {
//                 taskThreadId = std::this_thread::get_id();
//             } else {
//                 EXPECT_EQ(taskThreadId, std::this_thread::get_id());
//             }
//             counter++;
//             std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         });
//     }

//     // 等待所有任务完成
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     EXPECT_EQ(counter, 5);
//     pool.stop();
// }

// // 测试线程池的压力测试
// TEST_F(ThreadPoolTest, StressTest) {
//     ParallelThreadPool pool(8);
//     pool.start();

//     std::atomic<int> counter{0};
//     std::vector<std::future<void>> futures;
//     const int taskCount = 1000;

//     // 提交大量任务
//     for (int i = 0; i < taskCount; ++i) {
//         auto future = pool.commit([&counter]() {
//             counter++;
//             std::this_thread::sleep_for(std::chrono::microseconds(100));
//         });
//         futures.push_back(std::move(future));
//     }

//     // 等待所有任务完成
//     for (auto& future : futures) {
//         future.wait();
//     }

//     EXPECT_EQ(counter, taskCount);
//     pool.stop();
// }