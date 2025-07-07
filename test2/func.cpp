

#include <stdio.h>
#include <stdint.h>
void func(int a, int b, int c, int d, int e)
{
    printf("%d, %d, %d, %d, %d\n", a, b, c, d, e);
    a = 10;
}


int main(int argc, char* argv[])
{

    int a = 1;
    func(a, 2, 3, 4, 5);

    uint32_t bb = 467;
    bb &= ~1;

    printf("%d, %d \n", bb, bb);

    return 0;
}