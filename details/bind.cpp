

#include <functional>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#include <type_traits>

class A
{
public:
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }

    void print(int a)
    {
        _a = a;
        std::cout << "print: " << _a << std::endl;
    }

private:
    int _a = 0;
};


struct US
{

};

class UC
{

};


union PKDropInteractive
{
    uint64_t bits;
    struct 
    {
            //流的pk流 streamPK
            //信令pk流 clientPK
            //麦位数量  size
            //当前角色  rolePlay
            //当前是否连麦 isInteractive
            //分辨率    baseSize 

        uint64_t streamPK : 1;
        uint64_t clientPK : 1;
        uint64_t interactiveSize : 4;
        uint64_t role : 3;
        uint64_t isInteractive : 1;
        uint64_t baseWidth : 12;
        uint64_t baseHeight : 12;
    };
    
};

int main(int argc, char* argv[])
{

    // using Fun = std::function<void(int)>;

    // std::thread tt;
    // {
    //     Fun fun;

    //     {
    //         //对象a生命周期结束
    //         std::unique_ptr<A> a = std::make_unique<A>();
    //         fun  = std::bind(&A::print, a.get(), std::placeholders::_1);
    //     }

    //     int aa = 100;
    //     std::thread t([&aa](Fun fu){
    //         while(aa--)
    //         {
    //             fu(aa);
    //             std::this_thread::sleep_for(std::chrono::microseconds(10));
    //         }
    //     }, fun);
        
    //     fun(10);

    //     tt = std::move(t);
    // }

    // tt.join();

    // std::this_thread::sleep_for(std::chrono::seconds(5));
    

    // auto fun = []()->bool {
    //     return true;
    // };


    // US *a = new US;
    // int aa = 0;

    // std::cout << "is_function:" << std::is_function<decltype(fun)>::value << std::endl;
    // std::cout << "is_function:" << std::is_object<decltype(fun)>::value << std::endl;
    // std::cout << "is_function:" << std::is_class<US>::value << std::endl;
    // std::cout << "is_function:" << std::is_class<UC>::value << std::endl;

    // std::cout << "is_function:" << std::is_pointer<std::remove_reference< decltype(a) >::type>::value << std::endl;

    PKDropInteractive info;
    memset(&info, 0, sizeof(info));
    info.bits |= (1 << 0);   //0b 0000 0000 0000 0001
    info.bits |= (0 << 1);   //0b 0000 0000 0000 0000
    info.bits |= (12 << 2);  //0b 0000 0001 1000 0000
    info.bits |= (3 << 6);
    info.bits |= (0 << 9);
    info.bits |= (720 << 10);
    info.bits |= ((int64_t)1280 << 22);

    std::cout << "sizeof: " << sizeof(info) << std::endl;
    std::cout << " --- \n"
              << info.streamPK << ","
              << info.clientPK << ","
              << info.interactiveSize << ","
              << info.role << ","
              << info.isInteractive << ","
              << info.baseWidth << ","
              << info.baseHeight << std::endl; 


    return 0;
}

