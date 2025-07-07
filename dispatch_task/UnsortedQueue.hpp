#pragma once

#include "Task.h"
#include "ITaskQueue.h"
#include "concurrentqueue.h"

namespace task
{
class UnsortedQueue : public ITaskQueue
{
public:
    UnsortedQueue()
    {
        _freeQueue.reset(new LockFreeQueue);
    }
    virtual ~UnsortedQueue() = default;

    virtual void push(std::shared_ptr<Task> task) override
    {
        _freeQueue->enqueue(task);
    }

    virtual bool tryPop(std::shared_ptr<Task>& task) override
    {
        return _freeQueue->try_dequeue(task);
    }

    virtual void clear() override
    {
        _freeQueue.reset(new LockFreeQueue);
    }

    virtual uint32_t size() override
    {
        return static_cast<uint32_t>(_freeQueue->size_approx());
    }

    virtual bool empty() override
    {
        return size() == 0;
    }

private:
    using LockFreeQueue = moodycamel::ConcurrentQueue<std::shared_ptr<task::Task>>;
    std::unique_ptr<LockFreeQueue> _freeQueue;
};

}  // namespace task
