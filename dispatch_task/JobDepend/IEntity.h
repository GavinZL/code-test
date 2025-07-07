#pragma once

namespace task
{

class IEntity
{
public:

    virtual void onInitialze()  = 0;
    virtual void onProcess()    = 0; 
    virtual void onRelease()    = 0;

    //是否需要执行
    virtual bool needWorking()  =  0;
};


}

