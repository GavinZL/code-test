// 任务组
// 任务组是一组任务的集合，任务组的任务会被分配到不同的线程中执行

#ifndef __TASK_GROUP_H__
#define __TASK_GROUP_H__

#include <chrono>
#include <cstddef>
#include <memory>
#include "TaskQueueDefine.h"
namespace queue 
{
    class GroupImpl;
    class TaskGroup
    {
        public:
            TaskGroup(const std::shared_ptr<GroupImpl>& groupImpl)
            : mGroupImpl(groupImpl)
            {}

            ~TaskGroup() = default;

            // 在指定队列抛一个任务
            void async(const TaskOperatorPtr& task, const TaskQueuePtr& queue = nullptr);
            template<typename Func>
            void async(const Func& f, const TaskQueuePtr& queue = nullptr);

            // 在全局队列抛一个任务
            void async(const TaskOperatorPtr& task, TaskQueuePriority priority = TaskQueuePriority::TQP_Normal);
            template<typename Func>
            void async(const Func& f, TaskQueuePriority priority = TaskQueuePriority::TQP_Normal);

            // group所有执行完后，在指定queue上异步通知
            void notify(const TaskOperatorPtr& task, const TaskQueuePtr& queue = nullptr);
            template<typename Func>
            void notify(const Func& f, const TaskQueuePtr& queue = nullptr);

            // group 等待所有任务结束
            bool wait(std::chrono::milliseconds t = std::chrono::milliseconds(-1));

        private:
            std::shared_ptr<GroupImpl> mGroupImpl;
    } ;



    template<typename Func>
    void TaskGroup::async(const Func& f, const TaskQueuePtr& queue)
    {
        auto task = std::shared_ptr<TaskOperator>([f](const TaskOperatorPtr& task) {
            f();
        });
        async(task, queue);
    }


    template<typename Func>
    void TaskGroup::async(const Func& f, TaskQueuePriority priority)
    {
        auto task = std::shared_ptr<TaskOperator>([f](const TaskOperatorPtr& task) {
            f();
        });
        async(task, priority);
    }

    template<typename Func>
    void TaskGroup::notify(const Func& f, const TaskQueuePtr& queue)
    {
        auto task = std::shared_ptr<TaskOperator>([f](const TaskOperatorPtr& task) {
            f();
        });
        notify(task, queue);
    }

}


#endif // __TASK_GROUP_H__