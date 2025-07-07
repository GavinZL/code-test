#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <forward_list>
#include <mutex>

#include "IEntity.h"

#include "../TaskDispatcher.hpp"

namespace task
{

class EntityWrapper
{
public:
    EntityWrapper(const std::string& id, std::shared_ptr<IEntity> entity)
    : _name(id)
    , _entity(entity)
    {}
    
    void doWork(const std::shared_ptr<TaskDispatcher> &dispather);

    //添加前置依赖
    void addPrevDepend(std::shared_ptr<EntityWrapper>& depend);
    void setPrevDepend(std::forward_list<std::shared_ptr<EntityWrapper>>& depend);
    void delPrevDepend(std::shared_ptr<EntityWrapper>& depend);

    //添加后置被依赖
    void addNextDepend(std::shared_ptr<EntityWrapper>& depend);
    void setNextDepend(std::forward_list<std::shared_ptr<EntityWrapper>>& depend);
    void delNextDepend(std::shared_ptr<EntityWrapper>& depend);

    void pause();
    void resume();

    bool isDone();

    //重置状态
    void resetState();
    void setRunThread(int32_t tid);
    int32_t getRunThreadId()
    {
        return _threadId;
    }
    std::string_view name() {
        return _name;
    }
protected:
    void _doTask();
    void _doNext(const std::shared_ptr<TaskDispatcher> &dispather);

private:
    bool _isDependsEmpty();
    bool _isDependsFinished();
    bool _isWorkingAndDone();

private:
    int32_t                     _threadId   = -1;                  //需要指定线程执行
    std::string                 _name;
    std::shared_ptr<IEntity>    _entity;
    std::mutex                  _mutex;

    //当前entity的下游entity， 依赖此entity的节点集合
    std::forward_list<std::shared_ptr<EntityWrapper>> _nextEntities;

    //当前entity的上游entity， 执行此entity所依赖的节点集合
    std::forward_list<std::shared_ptr<EntityWrapper>> _dependEntities;

    enum EntityState
    {
        kEntityInitialized = 0,
        kEntityWorking,
        kEntityFinish,
        kEntityError
    };
    EntityState _state = kEntityInitialized;

};


}