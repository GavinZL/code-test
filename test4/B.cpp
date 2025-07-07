
//arm64
//xcrun -sdk iphoneos clang++ -arch arm64 -std=c++17 A.cpp B.cpp -o ABC

//clang++ -std=c+=17 -c A.cpp A.o
//clang++ -std=c+=17 -c B.cpp B.o
//ld A.o B.o -lSystem -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -o AB
//objdump -h A.o
//objdump -h B.o
//objdump -h AB
#include <stdio.h>

int x = 10;

extern void func();

int main()
{

    func();

    return 0;
}