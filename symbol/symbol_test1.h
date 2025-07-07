
#ifndef SYMBOL_TEST1_H
#define SYMBOL_TEST1_H

#define EXPOSE_API __attribute__((visibility("hidden")))

#include <stdint.h>

EXPOSE_API bool yuv_to_rgb(uint8_t* dstRGB, uint8_t* srcY, uint8_t* srcU, uint8_t* srcV, int width, int height, int isFullrange, int matrix);




#endif