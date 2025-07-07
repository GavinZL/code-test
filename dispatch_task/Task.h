
//分发任务，任务基类
#pragma once

#include <utility>
#include <cstdint>
#include <future>
#include <memory>
#include <functional>

#define DECLARE_VEARIABLE(type, name, default) \
public:                                        \
    inline const type& get##name() const       \
    {                                          \
        return ( const type& )_##name;         \
    }                                          \
    inline void set##name(type para)           \
    {                                          \
        _##name = para;                        \
    }                                          \
                                               \
private:                                       \
    type _##name = default;

namespace task
{
enum class TaskRunType : uint8_t
{
    TT_ASYNCHRONOUS = 0,
    TT_SYNCHRONOUS
};

class Task : public std::enable_shared_from_this<Task>
{
public:
    Task()          = default;
    virtual ~Task() = default;

    std::shared_ptr<Task> getSharedThis()
    {
        return shared_from_this();
    }

    bool doTask()
    {
        bool ret = _doTask();
        _syncFlag.set_value(true);  //表示执行完成
        return ret;
    }

    //此函数只能调用一次，std::promise中的future采用move操作
    std::future<bool> getFuture() const
    {
        return _syncFlag.get_future();
    }

    //设置回调
    using Callback = std::function<void(std::shared_ptr<Task>)>;
    void setCallback(Callback callback)
    {
        _callback = callback;
    }

    void setUserData(const std::shared_ptr<void>& data)
    {
        _userData = data;
    }

    template <typename T>
    std::shared_ptr<T> getUserData() const
    {
        return std::static_pointer_cast<T>(_userData);
    }

protected:
    virtual bool _doTask()
    {
        //继承自定义实现
        if (_callback)
        {
            _callback(getSharedThis());
        }

        return true;
    };

protected:
    Callback _callback = nullptr;

private:
    DECLARE_VEARIABLE(uint32_t, TaskId, 0);
    DECLARE_VEARIABLE(int32_t, ThreadId, -1);  ////固定一个线程id执行任务，如果未指定(-1),默认随机分配线程执行
    DECLARE_VEARIABLE(TaskRunType, TaskRunType, TaskRunType::TT_ASYNCHRONOUS);
    //    DECLARE_VEARIABLE(void*, UserData, nullptr);

    //可用于进行同步等待此task完成
    mutable std::promise<bool>    _syncFlag;
    mutable std::shared_ptr<void> _userData;
};
}  // namespace task
