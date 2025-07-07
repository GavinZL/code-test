
#include "stdio.h"
#include <cstddef>
#include <cctype>
#include <string>

class A
{
public:
    virtual ~A(){printf("~A\n");}
    inline void print()
    {

    }

private:
    int a = 0;
};

class B : public A
{
public:

};


const uint32_t placeholder_width = 200;
const uint32_t placeholder_height = 200;

uint8_t* getPlaceholderImage()
{   
    uint8_t rb = 4;
    uint8_t re = 0;
    uint8_t gb = 32;
    uint8_t ge = 21;
    uint8_t bb = 69;
    uint8_t be = 50;
    
    float yb = (0.257f * rb + 0.504f * gb + 0.098f * bb + 16);
    float ye = (0.257f * re + 0.504f * ge + 0.098f * be + 16);
    
    printf("y: %f - %f \n", yb, ye);
    float ub = (-0.148f * rb - 0.291f * gb + 0.439f * bb + 128);
    float ue = (-0.148f * re - 0.291f * ge + 0.439f * be + 128);
    
    float vb = (0.439f * rb - 0.368f * gb - 0.071f * bb + 128);
    float ve = (0.439f * re - 0.368f * ge - 0.071f * be + 128);

    printf("u: %f - %f \n", ub, ue);
    printf("v: %f - %f \n", vb, ve);

    uint8_t *placeholder_image = new uint8_t[placeholder_width * placeholder_height * 3 / 2];
    
    uint8_t *Y = placeholder_image;
    uint8_t *U = placeholder_image + placeholder_height * placeholder_width;
    uint8_t *V = placeholder_image + placeholder_width * placeholder_height * 5 / 4;
    float yStep = (ye - yb) / placeholder_height;
    printf("y: %f \n", yStep);
    uint8_t val = 0;
    for(int i=0; i<placeholder_height; ++i)
    {
        val = static_cast<uint8_t>(yb + i * yStep);
        memset(Y + i * placeholder_width, val, placeholder_width);
        printf("%d - ", val);
    }

    float uStep = (ue - ub) / placeholder_height;
    float vStep = (ve - vb) / placeholder_height;
    printf("u: %f, v: %f \n", uStep, vStep);
    uint32_t uvStride = placeholder_width / 2;
    for(int i=0, cnt=placeholder_height/2; i<cnt; ++i)
    {
        val = static_cast<uint8_t>(ub + i * uStep);
        memset(U + i * uvStride , val, uvStride);
        
        val = static_cast<uint8_t>(vb + i * vStep);
        memset(V + i * uvStride, val, uvStride);
    }

    return placeholder_image;
}


int main(int argc, char* argv[])
{

    B a;

    // a.print();

    uint8_t *yuv = getPlaceholderImage();
    
    FILE *fw = fopen("./test.yuv", "w");
    if(fw)
    {
        fwrite(yuv, 200 * 200 * 3 / 2, 1, fw);

        fclose(fw);
    }


    return 0;
}