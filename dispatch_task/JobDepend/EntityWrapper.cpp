#include "EntityWrapper.h"
#include "../Task.h"

#include <iostream>
namespace task
{

void EntityWrapper::doWork(const std::shared_ptr<TaskDispatcher> &dispather)
{   
    //1. 没有任何依赖，直接执行
    //2. 所有依赖都执行完成，执行自己
    if(_isDependsEmpty() || _isDependsFinished())
    {
        //判断自身是否执行过了,主要处理被依赖的节点同时执行完成，此处会收到两次执行消息，需要过滤掉一次
        if(!this->_isWorkingAndDone())
        {
            //1.执行自己的任务
            _doTask();
            //2. 执行完成后， 进行下一级任务执行
            _doNext(dispather);
        }
    }
}

//添加前置依赖
void EntityWrapper::addPrevDepend(std::shared_ptr<EntityWrapper>& depend)
{
    //TODO: 判重
    _dependEntities.push_front(depend);
}

void EntityWrapper::setPrevDepend(std::forward_list<std::shared_ptr<EntityWrapper>>& depend)
{
    _dependEntities.swap(depend);
}

void EntityWrapper::delPrevDepend(std::shared_ptr<EntityWrapper>& depend)
{

}

//添加后置被依赖
void EntityWrapper::addNextDepend(std::shared_ptr<EntityWrapper>& depend)
{
    //TODO: 判重
    _nextEntities.push_front(depend);
}

void EntityWrapper::setNextDepend(std::forward_list<std::shared_ptr<EntityWrapper>>& depend)
{
    _nextEntities.swap(depend);
}

void EntityWrapper::delNextDepend(std::shared_ptr<EntityWrapper>& depend)
{

}

void EntityWrapper::pause()
{

}

void EntityWrapper::resume()
{

}

bool EntityWrapper::isDone()
{
    return _state == kEntityFinish;
}

bool EntityWrapper::_isWorkingAndDone()
{
    return _state == kEntityWorking || _state == kEntityFinish;
}

void EntityWrapper::resetState()
{
    _state = kEntityInitialized;
}

void EntityWrapper::_doTask()
{
    //当前状态
    _state = kEntityWorking;

    if(_entity)
    {
        _entity->onProcess();
    }

    //赋值结束
    _state = kEntityFinish;
}

bool EntityWrapper::_isDependsFinished()
{
    //搜集依赖状态
    bool dependsNotFinished = false;
    for(const auto& depend : _dependEntities)
    {
        if(!depend->isDone())
        {
            dependsNotFinished = true;
        }
    }

    //所有依赖是否执行完成
    return !dependsNotFinished;
}

uint32_t gGenerateTaskId()
{
    static std::atomic<uint32_t> s_taskid = (1 << 10);
    return s_taskid.fetch_add(1);
}

void EntityWrapper::_doNext(const std::shared_ptr<TaskDispatcher> &dispather)
{
    //组装task，抛线程执行
    for(const auto& next : _nextEntities)
    {
        //组装task, 跑向子线程
        std::shared_ptr<task::Task> task = std::make_shared<task::Task>();
        task->setTaskId(gGenerateTaskId());
        task->setThreadId(next->getRunThreadId());
        // std::cout << "_doNext, "<< "name: "<< next->name() << ", threadid: " << next->getRunThreadId() << "\n";
        task->setCallback([&next, &dispather](std::shared_ptr<task::Task> tsk) {
            next->doWork(dispather);
        });

        dispather->dispatchTask(task);
    }
}


bool EntityWrapper::_isDependsEmpty()
{
    return _dependEntities.begin() == _dependEntities.end();
}

void EntityWrapper::setRunThread(int32_t tid)
{
    _threadId = tid;
}

}