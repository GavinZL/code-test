
#include <iostream>

class A;
A *g_A = nullptr;

//在A类的作用域范围内，是可以访问私有变量的，包括静态方法
class A {
    public:
    A(){

    }
    static void msgCallback(){
        std::cout << "aa:" << g_A->_aa++ << std::endl;
        std::cout << "aa:" << g_A->_aa++ << std::endl;
    }
    private:
        int _aa = 0;
};


int main(int argc, char* argv[]){

    A a;
    g_A = &a;
    
    // g_A->_aa = 100;      //不在A类的作用域内
    A::msgCallback();

    return 0;
}