
#include "libyuv.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>


// clang++ -std=c++14 -I ./include -L /System/Volumes/Data/opt/local/lib/ -llibyuv.a yuv.cpp -o t
int main(int argc, char* argv[])
{

    const char* path = "/Users/sdkteam/Downloads/410829988_20221130_184755.jpg";

//STBIDEF stbi_uc *stbi_load            (char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);

    int width = 0;
    int height = 0;
    int channel = 0;

    uint8_t* data = stbi_load(path, &width, &height, &channel, 3);
    if(data == nullptr)
    {
        return -1;
    }

    if(width <= 0 || height <= 0)
    {
        return -1;
    }

    printf("width: %d, height: %d, channel: %d\n", width, height, channel);

    uint32_t uisize = width * height;
    uint8_t *YUV = new uint8_t[uisize * 3 / 2];

    uint8_t *Y = YUV;
    uint8_t *U = YUV + uisize;
    uint8_t *V = YUV + uisize * 5/4;

    if(channel == 3){
        libyuv::RGB24ToI420(data, width * 4, Y, width, U, width/2, V, width/2, width, height);
    }

    int subWidth = 360;
    int subHeight = 640;
    uint32_t idsize = subWidth * subHeight;
    uint8_t *downSample = new uint8_t[idsize * 3 / 2];

    uint8_t *DY = downSample;
    uint8_t *DU = downSample + idsize;
    uint8_t *DV = downSample + idsize * 5 / 4;

    libyuv::I420Scale(Y, width, U, width/2, V, width/2, width, height, DY, subWidth, DU, subWidth/2, DV, subWidth/2, subWidth, subHeight, libyuv::kFilterBilinear);


    FILE *fp = fopen("./bilinear.yuv", "w");
    if(fp)
    {
        fwrite(downSample, idsize * 3 / 2, 1, fp);
        fclose(fp);
    }


    delete []YUV;
    delete []downSample;


    return 0;
}

