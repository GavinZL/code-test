

#include <stdio.h>


int main()
{

    int val = 0;

    int w = 720;
    int h = 1280;

    val |= w;
    val = val << 16;
    val |= h;

    printf("==> %d \n", val);

    int h0 = val & 0xffff;
    val = val >> 16;
    int w0 = val & 0xffff;

    printf("==> %d, %d \n", w0, h0);

}