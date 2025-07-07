//任务队列线程池
//支持固定线程 or 随机线程

#pragma once
#include "TaskThread.hpp"
#include <vector>
#include <utility>

namespace task
{

class TaskThreadPool
{
public:
    void initialize(uint16_t threadsCnt = 1);
    void destory();

    void pause();
    void resume();

    uint16_t getThreadCnt() const
    {
        return _threadCnt;
    }

    //设置固定线程
    void setFixThread(uint32_t index, bool fix);

    //获取固定线程
    const std::unique_ptr<task::TaskThread>& getThreadByIndex(uint32_t index) const;

    //默认获取任务量少的线程[简单的调度]
    const std::unique_ptr<task::TaskThread>& getThread() const;

protected:
    uint32_t _getConcurrentCoreCnt();

private:
    uint32_t                                       _threadCnt = 1;
    std::vector<std::unique_ptr<task::TaskThread>> _threads;
};

}  // namespace task
