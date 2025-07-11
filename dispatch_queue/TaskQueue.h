// 任务队列
#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__
#include <functional>
#include <memory>
#include <string>
#include "TaskQueueDefine.h"
#include "TaskOperator.h"
namespace task
{
    // 任务队列
    class TaskQueue final
    {
    public:
        using Func = std::function<void()>;
    public:
        explicit TaskQueue(const std::string& label, const TaskQueueImplPtr& impl);
        ~TaskQueue() = default;

        // 队列标签
        const std::string& label() const { return mLabel; }

        // 异步任务
        void async(const TaskOperatorPtr& task);
        // 直接使用std::functiond对象，处理lambda回调(参数由lambda捕获列表进行传递)
        void async(Func&& func) {
            auto task = std::make_shared<TaskOperator>([func](const TaskOperatorPtr&) {
                func();
            });
            async(task);
        }

        // 同步任务
        void sync(const TaskOperatorPtr& task);
        void sync(Func&& func) {
            auto task = std::make_shared<TaskOperator>([func](const TaskOperatorPtr&) {
                func();
            });
            sync(task);
        }

        // 延时任务
        void after(std::chrono::milliseconds delay, const TaskOperatorPtr& task);
        void after(std::chrono::milliseconds delay, Func&& func) {
            auto task = std::make_shared<TaskOperator>([func](const TaskOperatorPtr&) {
                func();
            });
            after(delay, task);
        }

        private:
            std::string mLabel;
            std::shared_ptr<class IQueueImpl> mImpl;
    };
}

#endif // __TASK_QUEUE_H__