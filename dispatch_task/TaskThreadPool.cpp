
#include "TaskThreadPool.hpp"

#include <thread>
#include <limits>
#include <vector>
#include <map>
#include <random>
#include <cstdio>
#include <iostream>

namespace task
{

void TaskThreadPool::initialize(uint16_t threadsCnt)
{
    _threadCnt = threadsCnt == 0 ? this->_getConcurrentCoreCnt() : threadsCnt;

    printf("thread count: %d\n", _threadCnt);
    for (int i = 0; i < _threadCnt; ++i)
    {
        _threads.emplace_back(std::make_unique<TaskThread>());
        _threads[i]->start();
    }
}

void TaskThreadPool::destory()
{
    for (int i = 0; i < _threadCnt; ++i)
    {
        _threads[i]->stop();
    }
}

void TaskThreadPool::pause()
{
    for (int i = 0; i < _threadCnt; ++i)
    {
        _threads[i]->pause();
    }
}

void TaskThreadPool::resume()
{
    for (int i = 0; i < _threadCnt; ++i)
    {
        _threads[i]->resume();
    }
}

void TaskThreadPool::setFixThread(uint32_t index, bool fix)
{
    if (index < 0 || index > _threads.size())
    {
        return;
    }

    _threads[index]->setFixThread(fix);
}

//获取固定线程
const std::unique_ptr<task::TaskThread>& TaskThreadPool::getThreadByIndex(uint32_t index) const
{
    if (index < 0 || index > _threads.size())
    {
        throw std::runtime_error("getThreadByIndex input param index invalid");
    }

    return _threads[index];
}


int32_t randomNumber(int32_t min, int32_t max)
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int32_t> distribution(min,max);
    return distribution(generator);
}

//默认获取任务量少的线程[简单的调度]
const std::unique_ptr<task::TaskThread>& TaskThreadPool::getThread() const
{
    uint16_t index    = 0;
    std::map<uint16_t, std::vector<uint16_t>, std::less<uint16_t>> mRandomThreads; //选择可以随机调度的线程<队列数量，线程集合>, 比如存储队列数量为0的线程id集合
    for (uint16_t i = 0; i < _threadCnt; ++i)
    {
        if (!_threads[i]->getFixThread())
        {
            mRandomThreads[_threads[i]->getTaskCnt()].push_back(i);
        }
    }

    //按升序获取运行线程id
    for(const auto& [key, value] : mRandomThreads)
    {
        uint16_t cnt = value.size();
        if(cnt > 0)
        {
            index = randomNumber(0, cnt-1);
        }
    }

    if (index < 0 || index > _threads.size())
    {
        throw std::runtime_error("getThread random index invalid");
    }
    
    return _threads[index];
}



uint32_t TaskThreadPool::_getConcurrentCoreCnt()
{
    return std::thread::hardware_concurrency();
}

}  // namespace task
