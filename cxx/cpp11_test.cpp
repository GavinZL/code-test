

#include <stdio.h>
#include <optional>

class A
{
public:
    A()
    {
        printf("A::A()\n");
    }
    A(int a)
    {
        printf("A::A(int)\n");
    }
    void f(int a)
    {
        printf("A::f(int)\n");
    }
};

class B : public A
{
public:
    using A::A;
    B()
    {
        printf("B::B()\n");
    }
    B(float b)
    {
        printf("B::B(float)\n");
    }

    using A::f;
    void f(double b)
    {
        printf("B::f(double)\n");
    }

private:
    int b {0};
};

int main(int argc, char* argv[])
{

    B b(1.0);
    b.f(3);

    return 0;
}