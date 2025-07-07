

#include <memory>
#include <cstdio>
#include <functional>
#include <utility>

template<typename T>
class Task : public std::enable_shared_from_this<Task<T>>
{
public:

    void fun(std::function<void(std::shared_ptr<Task<T>>)> call)
    {
        // printf("..... %p\n", call);
        call(getSharedPtr());
    }

    std::shared_ptr<Task<T>> getSharedPtr()
    {
        return this->shared_from_this();
    }   

    void print()
    {
        printf("....%p\n", this);
    }

private:

    T _data;
};



template<typename T>
class A
{
public:
};

template<typename T>
class B : public A<B<T>>
{

};


int main(int argc, char* argv[])
{


    // B<int> b;

    std::shared_ptr<Task<int>> task = std::make_shared<Task<int>>();

    task->fun([](std::shared_ptr<Task<int>> task)
    {
        task->print();
    });


    return 0;
}