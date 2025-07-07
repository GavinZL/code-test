

#include <vector>
#include <iostream>
#include <stdio.h>
#include <string_view>
#include <optional>

int main(int argc, char* argv[])
{
    std::vector<uint8_t> mImageData;
    mImageData.reserve(5);

    int32_t width = 2;
    int32_t height = 2;
    mImageData.resize(5);

    // std::cout << "px: " << mImageData.data() << std::endl;
    printf("px: %p, i: %p\n", mImageData.data(), &mImageData);
    if(width * height != mImageData.size()){
        std::vector<uint8_t> v(width * height, 0);
        
        printf("vx: %p, v:%p \n", v.data(), &v);
        std::swap(mImageData, v);

        mImageData.resize(width * height);
    }

    std::cout << "image size : " << mImageData.size() 
    << ", px: " << mImageData.data() << std::endl;
    printf("px2: %p, i: %p\n", mImageData.data(), &mImageData);



    std::string ss;
    std::string_view v(ss);
    
    // value  注意引用类型（目前是ill-format）
    // engage 表示是否有值
    std::optional<int> o = 100;
}