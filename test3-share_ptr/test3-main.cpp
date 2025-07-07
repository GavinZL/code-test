

#include "test3-share_ptr.h"

#include <memory>

std::shared_ptr<B> _GetCameraListenerSharePtr(std::weak_ptr<B> ptr) {
    std::shared_ptr<B> listen = ptr.lock();
    return listen;
}
int main(){

    // B *b = new B();
    // b->Boo();


    std::shared_ptr<B> bb = std::make_shared<B>();
    std::weak_ptr<B> cc = bb;

    // decltype(bb) bc = cc.lock();
    // if( bc != nullptr){
    //     bc->Boo();
    // }

    auto bc = _GetCameraListenerSharePtr(cc);
    if(bc != nullptr){
        bc->Boo();
    }

    return 0;
}