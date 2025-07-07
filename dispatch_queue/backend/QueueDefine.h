// 线程池枚举定义

#ifndef __HETHREADDEFINE_H__
#define __HETHREADDEFINE_H__

#include <cstdint>
#include "3rdparty/concurrentqueue.h"

namespace queue 
{

    class TaskOperator;
    class IThreadPool;

}

// 无锁并发队列
using WorkQueue = moodycamel::ConcurrentQueue<std::shared_ptr<queue::TaskOperator>>;
using ThreadPoolPtr = std::shared_ptr<queue::IThreadPool>;

#endif