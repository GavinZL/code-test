// 线程池枚举定义

#ifndef __HETHREADDEFINE_H__
#define __HETHREADDEFINE_H__

#include <cstdint>
#include "3rdparty/concurrentqueue.h"

namespace task 
{

    class TaskOperator;
    class IThreadPool;

}

// 无锁并发队列
using WorkQueue = moodycamel::ConcurrentQueue<std::shared_ptr<task::TaskOperator>>;
using ThreadPoolPtr = std::shared_ptr<task::IThreadPool>;

#endif