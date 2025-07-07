/*** @brief 单例模版*/

#pragma once

namespace comm
{
template <typename T>
class HESingleton
{
public:
    HESingleton(const HESingleton&) = delete;
    HESingleton(HESingleton&&)      = delete;
    HESingleton& operator=(const HESingleton&) = delete;
    HESingleton& operator=(HESingleton&&) = delete;

protected:
    HESingleton() = default;

public:
    virtual ~HESingleton() noexcept = default;

    static T& GetInstance() noexcept
    {
        static T sInstance;
        return sInstance;
    }
};
}  // namespace comm
