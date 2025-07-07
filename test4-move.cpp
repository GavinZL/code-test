
#include <stdio.h>

#include <functional>
#include <thread>
#include <memory>
#include <unistd.h>

class A{
public:
    void PrintA(){
        printf("A\n");
    }
};


class IParam{
public:
    IParam(){
        printf("IParam \n");
    }
    virtual ~IParam(){
        printf("~IParam \n");
    }

    int a;
};

class Param : public IParam{
public:
    int key;
    int data;
    Param(){
        printf("Param\n");
    }

    virtual ~Param(){
        printf("~Param\n");
    }

    Param& operator = (Param&& param){
        key = param.key;
        data = param.data;
        param.data = 0;
        printf("Param operator = &&\n");

        return *this;
    }

    Param(Param && param){
        key = param.key;
        data = param.data;
        param.data = 0;
        printf("Param &&\n");
    }

};





using Delegate = std::function<int (const int& , std::unique_ptr<IParam>)>;

Delegate s_delegate;


void func(){

    if(s_delegate){

        std::unique_ptr<Param> p(new Param());
        p->key = 0;
        p->data = 1;

        s_delegate(0, std::move(p));
    }
}


std::unique_ptr<IParam> fun(const std::unique_ptr<IParam>& para){

    std::unique_ptr<IParam> pa = para;
    return std::move(pa);
}


int main()
{

    std::shared_ptr<IParam> sp;
    std::weak_ptr<IParam> wp;
    // std::unique_ptr<IParam> pp;

    // s_delegate = [&pp](const int& key, std::unique_ptr<IParam> p)->int{

    //     printf("t->key: %d \n", key);
    //     if(key == 0){
    //         Param *pc = static_cast<Param*>( p.get() );
    //         printf("t->p->key: %d , data: %d \n", pc->key, pc->data);
    //     }

    //     pp = std::move(p);
    //     return 0;
    // };


    // std::thread t(func);

    // // int n = 1000;
    // // while(n > 0){
    // //     n--;
    // //     usleep(1000);
    // //     // printf(".");
    // // }
    // t.join();



    std::unique_ptr<IParam> t1(new Param());


    std::unique_ptr<IParam> t2 = fun(t1);

    // printf("pp->key: %d, pp->data: %d \n", pp->key, pp->data);
    printf("end \n");
    return 0;
}
