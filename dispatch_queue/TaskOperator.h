#ifndef __TASK_OPERATOR_H__
#define __TASK_OPERATOR_H__
#include <memory>
#include <functional>
namespace queue 
{
    class TaskOperator : public std::enable_shared_from_this<TaskOperator>
    {
    public:
        using CallBack = std::function<void(const std::shared_ptr<TaskOperator>&)>;
        
    public:
        TaskOperator() = default;

        explicit TaskOperator(CallBack callback) 
        : mCallBack(std::move(callback)) 
        {}

        virtual ~TaskOperator() = default;

        virtual void operator()()
        {
            if(mCallBack)
            {
                mCallBack(shared_from_this());
            }
        }

        // 用户数据
        void setUserData(const std::shared_ptr<void>& userData) 
        { 
            mUserData = userData; 
        }

        template<typename T>
        std::shared_ptr<T> userData() const 
        { 
            return std::static_pointer_cast<T>(mUserData); 
        }

    private:
        CallBack mCallBack;
        mutable std::shared_ptr<void> mUserData;
    };
}

#endif