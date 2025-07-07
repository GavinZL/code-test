

#include <stdio.h>
#include <typeinfo>
#include <functional>
#include <tuple>

void fun(const char* v)
{
    printf("%s\n", v);
}


#define PRINT(v) fun(#v)

class A
{

};

template<typename T>
struct TypeParseTraits;

#define REGISTER_PARSE_TYPE(X) template <> struct TypeParseTraits<X> \
    { static const char* name; } ; const char* TypeParseTraits<X>::name = #X; \


REGISTER_PARSE_TYPE(int)
REGISTER_PARSE_TYPE(A)

template <typename T>
void func()
{
    printf("%s\n", TypeParseTraits<T>::name);
}



class Event
{
public:
    int mType;
};

template <typename... Args>
class CommonEvent : public Event
{
    public:
    CommonEvent(Args&& ...args)
    : _inTupleParams(std::make_tuple(std::forward<Args&&>(args)...))
    {
        ;
    }

    //输入参数
    std::tuple<Args&&...> _inTupleParams;

    //返回参数
    template<typename... ArgsBack>
    using CallbackFunctor = std::function<void(ArgsBack&&...)>;

    
};


int main(int argc, char* argv[])
{

    // func<int>();
    // func<A>();

}