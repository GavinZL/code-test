#include "test3-share_ptr.h"

#include "test3-classA.h"


void B::Boo(){
    mA.reset(new A());

    mA->Print();
}