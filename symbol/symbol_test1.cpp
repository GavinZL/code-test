#include "symbol_test1.h"

#include <string>

bool yuv_to_rgb(uint8_t* dstRGB, uint8_t* srcY, uint8_t* srcU, uint8_t* srcV, int width, int height, int isFullrange, int matrix)
{
    // check pointer input
    // if (dstRGB == nullptr || srcY == nullptr || srcU == nullptr || srcV == nullptr) return false;
    // // check sizes
    // if (width <= 0 || height <= 0) return false;
    // // check matrix type
    // if (matrix != 601 && matrix != 709) return false;

    // void (*yv12_to_rgb)(uint8_t * ybuf, int ystride, uint8_t* ubuf, int ustride, uint8_t* vbuf, int vstride, uint8_t* rgb, int stride, int width, int height) = yv12_to_rgb_bt601_fullrange_c;

    // int cpu = GetCPUFeature();
    // if (isFullrange)
    // {
    //     if (matrix == 601)
    //     {
    //         yv12_to_rgb = yv12_to_rgb_bt601_fullrange_c;
    //     }
    //     if (matrix == 709)
    //     {
    //         yv12_to_rgb = yv12_to_rgb_bt709_fullrange_c;
    //     }
    // }
    // else
    // {
    //     if (matrix == 601)
    //     {
    //         yv12_to_rgb = yv12_to_rgb_bt601_videorange_c;
    //     }
    //     if (matrix == 709)
    //     {
    //         yv12_to_rgb = yv12_to_rgb_bt709_videorange_c;
    //     }
    // }
    // if (/* DISABLES CODE */(0))
    // {
    //     yv12_to_rgb = nullptr;
    // }

    // int ystride = width;
    // // for odd width, ustride and vstride is (width + 1) / 2; for even width, is width / 2, also equals to (width + 1) / 2;
    // int ustride = (width + 1) / 2;
    // int vstride = ustride;

    // if (yv12_to_rgb == nullptr) return false;
    // yv12_to_rgb(srcY, width, srcU, ustride, srcV, vstride, dstRGB, width * 3, width, height);

    return true;
}