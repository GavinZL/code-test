//<! 线程池设计问题： 
//<!    1. 可使用的线程数量 , 2.高效的任务分配方式， 3. 是否需要等待一个任务完成
//<!    任务队列，线程集合

//异步编程期望目标：
//1. 将不同任务(Task)分配到不同线程执行(线程支持优先级)
//2. 解决不同Task之间资源的依赖关系

//thread:
//.yield 退出cpu占用时间片，重新接受操作系统调度
//.sleep_for 阻塞当前线程，睡眠指定的时长 ， 让出cpu时间片， std::this_thread::sleep_for(1ms)
//.sleep_until 

//资源竞争
//互斥锁
//1.mutex [不可复制， 不可move]
//2.recursive_mutex 递归锁，可重入同一个线程
//3.timed_mutex 带时间控制的mutex
//4.shared_mutex 读写锁， 写时lock/try_lock, 读时lock_shared/try_lock_shared

//加锁操作
//lock_guard  mutex的wrapper， 只支持一个mutex，不支持手动lock/unlock
//scoped_lock 支持多个mutex， c++17
//unique_lock

//线程同步
//条件变量
//1. condition_variable 

#include <thread>
#include <mutex>
#include <string_view>
#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <utility>
#include <numeric>
#include <array>
// int main(int argc, char* argv[])
// {
//     std::mutex g_mutex;
//     auto func = [](std::string_view str, std::mutex &mutex)
//     {
//         std::unique_lock<std::mutex> lock(mutex);
//         std::cout << "id: " << std::this_thread::get_id() << ", " << str << "\n";
//     };


//     std::thread t(func, "hello", std::ref(g_mutex));

//     func("world ", g_mutex);

//     t.join();

//     return 0;
// }


//future & promise
//packaged_task 
//async
void acc(const std::vector<int>::iterator& first, const std::vector<int>::iterator& end, std::promise<int> &mise)
{
    int sum = std::accumulate(first, end, 0);
    mise.set_value(sum);
}

int main(int argc, char* argv[])
{

    //future 用来访问异步操作的结果，可以查询异步状态： deferred:异步操作还没开始， ready:异步操作已经完成, timeout: 异步操作超时
    //promise (包装一个值 和 future绑定）
    try
    {
        std::vector<int> nums = {1, 2, 3, 4, 5};
        std::promise<int> promise;
        std::future<int> future = promise.get_future();

        std::thread t(acc, nums.begin(), nums.end(), std::ref(promise));

        std::cout << "result: " << future.get() << "\n";

        t.join();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    //packaged_task （包装一个异步操作[函数],和future绑定）
    std::packaged_task<int(int , int)> task([](int a, int b)
    {
        return std::pow(a, b);
    });

    std::future<int> pfuture = task.get_future();

    std::thread t2(std::move(task), 2, 10);

    std::cout << "result : " << pfuture.get() << std::endl;
    t2.join();
    

    auto funAsync = [](std::string_view str) -> std::string_view
    {
        std::cout << "thread_id: " << std::this_thread::get_id() << " , " << str << "\n";
        return str;
    };

    std::cout << "main: " << std::this_thread::get_id() << "\n";

    auto a1 = std::async(funAsync, "A");
    std::cout << "a1: " << a1.get() << "\n";

    auto a2 = std::async(std::launch::deferred, funAsync, "B");
    std::cout << "a2: " << a2.get() << "\n";

    auto a3 = std::async(std::launch::async, funAsync, "C");
    std::cout << "a3: " << a3.get() << "\n";



    std::array<std::string, 7> chars{"A", "B", "C", "D", "E", "F", "G"};
    for(const auto& ch : chars)
    {
        auto a = std::async(std::launch::async, funAsync, ch);
    }

}