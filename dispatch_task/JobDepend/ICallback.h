#pragma once

namespace task
{

class ICallback
{
public:
    //开始执行
    virtual void begin() = 0;

    //执行结束
    virtual void done() = 0;
};

}