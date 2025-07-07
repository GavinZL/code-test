// 任务队列
#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__
#include <functional>
#include <memory>
#include <string>
#include "TaskQueueDefine.h"
#include "TaskOperator.h"
namespace queue
{
    // 任务队列
    class TaskQueue final
    {
    public:
        explicit TaskQueue(const std::string& label, const TaskQueueImplPtr& impl);
        ~TaskQueue() = default;

        // 队列标签
        const std::string& label() const { return mLabel; }

        // 异步任务
        void async(const TaskOperatorPtr& task);

        template<typename Func, typename... Args>
        void async(Func&& func, Args&&... args);

        // 同步任务
        void sync(const TaskOperatorPtr& task);

        template<typename Func, typename... Args>
        void sync(Func&& func, Args&&... args);

        // 延时任务
        void after(std::chrono::milliseconds delay, const TaskOperatorPtr& task);

        // 延时任务
        template<typename Func, typename... Args>
        void after(std::chrono::milliseconds delay, Func&& func, Args&&... args);

        private:
            std::string mLabel;
            std::shared_ptr<class IQueueImpl> mImpl;
    };

    template<typename Func, typename... Args>
    void TaskQueue::async(Func&& func, Args&&... args)
    {
        auto task = std::make_shared<TaskOperator>([func, args...](const TaskOperatorPtr& task) {
            // func(std::forward<Args>(args)...);
        });
        async(task);
    }

    template<typename Func, typename... Args>
    void TaskQueue::sync(Func&& func, Args&&... args)
    {
        auto task = std::make_shared<TaskOperator>([func, args...](const TaskOperatorPtr& task) {
            // func(std::forward<Args>(args)...);
        });
        sync(task);
    }

    template<typename Func, typename... Args>
    void TaskQueue::after(std::chrono::milliseconds delay, Func&& func, Args&&... args)
    {
        auto task = std::make_shared<TaskOperator>([func, args...](const TaskOperatorPtr& task) {
            // func(std::forward<Args>(args)...);
        });
        after(delay, task);
    }
}

#endif // __TASK_QUEUE_H__