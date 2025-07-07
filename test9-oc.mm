#import <stdio.h>
//寻址：
//寄存器寻址： movl %eax %edx
//立即数寻址： movl $0x123, %edx
//直接寻址:  movl 0x1243, %edx
//间接寻址:  movl (%ebx) %edx

//指令：
//movb（8位）、movw（16位）、movl（32位）、movq（64位）
// #include <iostream>

// void add(int &a){
//     a++;
// }

// const int DD = 1000;
// const char* PP = "Hello world\n";

// __attribute__((visibility("default"))) int add(int i, int j){
//     return i+j;
// }

int main(int argc, char* argv[]){

    //printf("========\n");

    // int a = 10;
    // add(a);

    // const int aa = add(3, 7);

    // int* bb = (int*)&aa;

    // *bb = 200;


    // int cc = aa;
    // int dd = *bb;
    // std::cout << "aa=" << aa << ", "<< &aa << std::endl;
    // std::cout << "bb=" << *bb << ", "<< bb << std::endl;

    int a = -1; // 原码：00000000 00000001 --> 取反：11111111 11111110 --> 补码(+1): 11111111 11111111
    unsigned int b = 2;

    decltype(a + b) c = -10; //

    int d = (1 << 16);//  0001 0000 0000 0000 0000
    long e = (1 << 32);//  0001 0000 0000 0000 0000 0000 0000 0000 0000

    printf("%u, %d, %u ,%u , %lu\n", a, b, c, d, e);

    return 0;
}
