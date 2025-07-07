

#include <vector>
#include <memory>
#include <stdio.h>
#include <string>

#include <numeric>
#include <iostream>

class A{
public:
    int a;
};

#define SUBTYPE(type, value) ((type) | (value))
#define TYPE(type, subtype) ((uint64_t)(type) & (uint64_t)(subtype))
enum class CaptureSceneType : uint64_t{
    kScene_Unkown           = 0,                                                //!< unknown
    kSceneVideo             = 1 << 3,                                           //!< 视频, 默认前置
    kSceneVideo_Front       = SUBTYPE(kSceneVideo, 1),                          //!< 视频, 前置
    kSceneVideo_Rear        = SUBTYPE(kSceneVideo, 2),                          //!< 视频, 后置
    kScenePhoto             = 1 << 6,                                           //!< 拍照, 默认前置
    kScenePhoto_Front       = SUBTYPE(kScenePhoto, 1),              //!< 拍照, 前置
    kScenePhoto_Rear        = SUBTYPE(kScenePhoto, 2),              //!< 拍照, 后置
    kSceneAR                = 1 << 9,                                          //!< AR, 默认后置
    kSceneAR_Front          = SUBTYPE(kSceneAR, 1),                  //!< AR, 前置
    kSceneAR_Rear           = SUBTYPE(kSceneAR, 2),                  //!< AR, 后置
    kSceneVideo_Dual        = 1 << 12,                                          //!< 视频双摄像机(支持前置后置同时打开)
};

std::string ToBinary(CaptureSceneType c) {
    std::string res;
    uint64_t t = (uint64_t)c;
    for (int count = 0; count < 24 ; count++) {                                                                                                   
        char s = 0x1;
        s &= t;
        res += s + '0';
        t = t >> 1;
    }   
    return res;
}


int myfunction (int x, int y) {return x+2*y;}
struct myclass {
	int operator()(int x, int y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
        return x+3*y;
    }
} myobject;


int main(){

    printf("%06ld - %s \n", CaptureSceneType::kSceneVideo, ToBinary(CaptureSceneType::kSceneVideo).c_str());
    printf("%06ld - %s \n", CaptureSceneType::kSceneVideo_Front, ToBinary(CaptureSceneType::kSceneVideo_Front).c_str());
    printf("%06ld - %s \n", CaptureSceneType::kSceneVideo_Rear, ToBinary(CaptureSceneType::kSceneVideo_Rear).c_str());

    printf("%06ld - %s \n", CaptureSceneType::kScenePhoto, ToBinary(CaptureSceneType::kScenePhoto).c_str());
    printf("%06ld - %s \n", CaptureSceneType::kScenePhoto_Front, ToBinary(CaptureSceneType::kScenePhoto_Front).c_str());
    printf("%06ld - %s \n", CaptureSceneType::kScenePhoto_Rear, ToBinary(CaptureSceneType::kScenePhoto_Rear).c_str());

    printf("%06ld - %s \n", CaptureSceneType::kSceneAR, ToBinary(CaptureSceneType::kSceneAR).c_str());
    printf("%06ld - %s \n", CaptureSceneType::kSceneAR_Front, ToBinary(CaptureSceneType::kSceneAR_Front).c_str());
    printf("%06ld - %s \n", CaptureSceneType::kSceneAR_Rear, ToBinary(CaptureSceneType::kSceneAR_Rear).c_str());

    printf("%06ld - %s \n", CaptureSceneType::kSceneVideo_Dual, ToBinary(CaptureSceneType::kSceneVideo_Dual).c_str());


    printf("%06d - %06d \n", TYPE(CaptureSceneType::kSceneVideo, CaptureSceneType::kSceneVideo_Front), TYPE(CaptureSceneType::kSceneVideo, CaptureSceneType::kSceneVideo_Rear));
    printf("%06d - %06d \n", TYPE(CaptureSceneType::kScenePhoto, CaptureSceneType::kScenePhoto_Front), TYPE(CaptureSceneType::kSceneVideo, CaptureSceneType::kScenePhoto_Rear));
    printf("%06d - %06d \n", TYPE(CaptureSceneType::kSceneAR, CaptureSceneType::kSceneAR_Front), TYPE(CaptureSceneType::kSceneVideo, CaptureSceneType::kSceneAR_Rear));


    int init = 100;
    int numbers[] = {10,20,30};
    // std::cout << "using custom function: ";
    // std::cout << std::accumulate (numbers, numbers+3, init, myfunction);
    // std::cout << '\n';

    std::cout << "using custom object: " << std::endl;
    std::cout << std::accumulate (numbers, numbers+3, init, myobject);
    std::cout << '\n';

    return 0;
}