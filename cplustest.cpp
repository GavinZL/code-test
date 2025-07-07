


// void fact_helper(int x,int *res){
//    if(x<=1){
//        return;
//    }else{
//        int z=*res*x;
//        *res=z;
//        fact_helper(x-1,res);
//    }
// }

// int sfact(int x){
//       int val=1;
//       fact_helper(x,&val);
//       return val;
// }

// int main(void){
//      sfact(4);
//      return 0;
// }

#include <string>
#include <vector>
#include <chrono>

#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iostream>

#include <stdio.h>

void display(int &&n){
}

//// std::move
class MoveTest{
public:
    MoveTest(){std::cout << "MoveTest()" << std::endl;}
    MoveTest(const MoveTest& mv) {std::cout << "MoveTest(const MoveTest&)" << std::endl;}
    MoveTest(MoveTest&& mv){std::cout << "MoveTest(MoveTest&&) " << std::endl;}
    ~MoveTest(){std::cout << "~MoveTest()" << std::endl;}
    MoveTest& operator = (const MoveTest&) {std::cout << "MoveTest& operator = (const MoveTest&)" << std::endl; return *this;}
    MoveTest& operator = (MoveTest&&) {std::cout << "MoveTest operator = (MoveTest&&)" << std::endl; return *this;}
};


#define STR_NAME(x) #x

enum A
{
    TYPE_AA,
    TYPE_BB
};

int main(void){
/***********************************************************/
// 测试 函数与move的反汇编，左值与右值区别
// 结论： 1. 左值存与raw中， 即内存中， 右值存与寄存器中
//       2. 
/***********************************************************/

    // int &&a = 5;        // 5-->存储到内存(-20(%rbp)) --> 加载到寄存器(%rcx) --> 在mov到内存中(-16(%rbp))
    // int i = 22;
    // int j = std::move(i); // 22 --> -8(%rbp) --> %rdi --> (move调用) -8(%rbp) --> %rax --> -12(%rbp)
    // display(std::move(i));

/***********************************************************/
// 测试std resize, swap, reserve 耗时
// 结论： 1.采用reserve的方式，进行copy，比resize方式快
//       2.采用swap方式， 比std::move方式快
/***********************************************************/
    // int width = 720;
    // int height = 1280;
    // int channel = 4;
    // std::string data;
    // // data.resize(width * height * channel);
    // // memset(&data[0], 128, width * height * channel);

    // std::vector<int> vec;
    // vec.resize(width * height);
    // memset(&vec[0], 100, width * height);

    // std::string moveData;
    // std::vector<int> moveVec;
    // auto s = std::chrono::steady_clock::now();
    // // moveData.resize(width * height * channel);
    // // moveData = std::move(data);

    // moveVec.reserve(width * height);
    // // moveVec.resize(width * height);
    // // moveVec = std::move(vec);
    // memcpy((int*)moveVec.data() + width, (int*)vec.data() + width, width * (height-1));

    // auto e = std::chrono::steady_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(e - s).count() / 1000.0f;
    // printf("*****  move %0.6f ms, %p, %p\n", duration, &moveVec, &vec);
    // // printf("=----> %d - %d \n", moveVec[0], vec[0]);

    // std::string swapData;
    // std::vector<int> swapVec;
    // s = std::chrono::steady_clock::now();
    // // swapData.resize(width * height * channel);
    // // swapData.swap(data);
    // // swapVec.resize(width * height);
    // swapVec.swap(vec);
    // e = std::chrono::steady_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(e - s).count() / 1000.0f;
    // printf("*****  swap %0.6f ms, %p, %p\n", duration, &swapVec, &vec);

/***********************************************************/
// 测试 swap结果
// 结论：将aa中字符串的值，移到了bb字符串中，bb不需要resize操作
/***********************************************************/
    // std::string aa("aa");
    // std::string bb;
    // bb.swap(aa);
    // printf("aa:%s, bb: %s \n", aa.c_str(), bb.c_str());

/***********************************************************/
// 测试 std::string aa 是堆地址，还是栈地址
// 结论：是栈地址
/***********************************************************/
    // std::string aa("aa");
    // std::string* pp = new std::string();
    // printf("const string: %p \n", &"aa");
    // printf("string : %p \n", &aa);
    // printf("string pointer: %p \n", pp);

    // int ia = 0;
    // int *pa = new int;
    // printf("const int : %p \n", (void*)0);
    // printf("stack int : %p \n", &ia);
    // printf("heap int : %p \n", pa);


/***********************************************************/
// 测试 位操作
// 结论： ～ 取反操作 （原码， 补码）
//       正数的补码 == 原码,  [ 1 -> 原码： 0000 0001 , 补码取反， 1111 1110 ] [通过补码求原码: 1 -> 补码: 1111 1110 , (减1取反)原码: 1111 1101 -> 1000 0010]
//       负数的补码 == 符号位不变，原码取反再加1
//       取反操作:  ~a = -(a+1)
/***********************************************************/
    // //取 16位对齐
    // int base = 10;
    // int aligned = (base + 15) & ~15;
    // printf("--> aligned : %d - (~15):%d - (~1):%d \n", aligned, ~15, ~1);

    // int width = 2;
    // width &= ~(2 - 1);

    // printf("--> width: %d , (%d)\n", width, ~1);



/***********************************************************/
// 测试 move
// 结论： 
/***********************************************************/
    // MoveTest t2;
    // {
    //     MoveTest t1;
    //     t2 = std::move(t1);
    // }
    // std::cout << "----------" << std::endl;

    // int a = 1;
    // int b = 2;
    // a = std::move(b);
    // std::cout << "a: " << a << ", b: " << b << std::endl;

    // std::string aa = "aaaa";
    // std::string bb = "bbbb";
    // aa = std::move(bb);
    // std::cout << "aa: " << aa << ", bb: " << bb << std::endl;

    // std::vector<int> aaa;
    // aaa.push_back(1);aaa.push_back(1);aaa.push_back(1);
    // std::vector<int> bbb;
    // bbb = std::move(aaa);
    // std::cout << "aaa: " << aaa.size() << ", bbb: " << bbb.size() << std::endl;

    // int *t = new int(2);
    // int *y = new int(3);
    // int tt = std::move(*t);
    // int *yy = std::move(y);
    // std::cout << "t: " << t << ", " << *t << ","
    //           << "y: " << y << ", " << *y << ","
    //           << "tt: " << &tt << ", " << tt << ", "
    //           << "yy: " << yy << ", " << *yy << std::endl;


    printf("----> %s\n", STR_NAME(TYPE_AA));

    return 0;
}