

// void funB()
// {

// }

// static void func(int a)
// {
//     int b = a;
// }


int aaaaa = 9;
int bbbbb;
static int ccccc = 0;
static int ddddd;
const int eeeee = 10;
static const int fffff = 11;

const char* const abc = "aaaaabbbbbcccc";
static const char* const bcdef = "aaasfsafasdfsadfabbbbbcccc";


const char* const arr[] = 
{
    "A",
    "AB",
    "ABC"
};

// class A
// {
// public:
//     void fun1()
//     {

//     }
//     static void fun2();

//     virtual void fun3()
//     {

//     }

// public:
//     int a = {0};
//     int b ;
//     static int c;
// };

// int A::c = 0;
// void A::fun2()
// {

// }

int main(int argc, char* argv[])
{

    // func(2);
    // funB();
    ccccc = 11;
    ddddd = 222;

    int x = eeeee;
    int y = fffff;


    const char* p = bcdef;
    const char* pp = arr[0];
    // A a;
    // a.fun1();
    // a.fun2();
    // a.fun3();

    // a.a = 11;
    // a.b = 12;
    // A::c = 10;


    return 0;
}