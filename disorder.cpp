
#include <thread>
#include <stdio.h>


int a = 0;
int b = 0;

void fun1(){
    a = 1;
    b = 2;

    printf("fun1: a = %d, b = %d \n", a, b);
}

void fun2(){
    printf("fun2: a = %d, b = %d \n", a, b);
}


int main(int argc, char* argv[]){

    std::thread t1(fun1);
    std::thread t2(fun2);

    t1.join();
    t2.join();

    return 0;
}

