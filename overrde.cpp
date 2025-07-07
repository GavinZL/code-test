
#include <stdio.h>
#include <utility>
class A{
public:
static int AAA ;

void funA(){
    printf("A -- funA\n");
}

void funB(){
    printf("A -- funB\n");
}

};

int A::AAA = 100;


class B : public A{
public:

void funB(){
    printf("B -- funB \n");
}

};

std::pair<A*, B*> retTest(bool flag, A* a, B* b){
    //return flag ? b : a;
    if(flag){
        return std::make_pair<A*, B*>(a, nullptr);
    }else{
        return std::make_pair<A*, B*>(nullptr, b);
    }
}


int main(int argc, char* argv[]){

    A *a = new A();
    B *b = new B();

    a->funA();
    a->funB();
    printf("A: %d \n", a->AAA);
    // b->funA();
    b->funB();
    printf("B: %d \n", b->AAA);
printf("--------\n");
    // auto aa = true? a: b;
    // aa->funB();

    // auto bb = false? a: b;
    // bb->funB();

    auto aaa = retTest(true, a, b);
    {
        
    }
    aaa->funB();


    // auto cc = false ? a : b;
    // cc->funB();


    return 0;
}