


#include <stdio.h>
#include <thread>
#include <functional>
#include <memory>



class IParam{
    public:
    int x;
    int y;
};

using Callback = std::function<void(int key, std::unique_ptr<IParam>)>;

void run(Callback b){
    if(b != nullptr){
        std::unique_ptr<IParam> pa(new IParam);
        pa->x = 10;
        pa->y = 11;
        b(0, std::move(pa));
    }
}

int main()
{
    auto callback = []( int key, std::unique_ptr<IParam>){
        printf("callback *******.\n");
    };
    std::thread t(&run, callback);
    t.join();
    return 0;
}