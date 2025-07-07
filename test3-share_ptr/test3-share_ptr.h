#pragma once


#include <stdio.h>
#include <memory>

class A;
class B {
    public:
        void Boo();
        
    private:
        /// 主要测试，使用share_ptr应用在 class A前置申明上是否可以使用
        /// 结论： 是可以使用的
        std::shared_ptr<A> mA = nullptr;  
};