#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include "IEntity.h"
#include "EntityWrapper.h"

namespace task
{

class EntityWrapperBuilder
{
public:

    EntityWrapperBuilder& name(const std::string &name)
    {
        _name = name;
        return *this;
    }

    EntityWrapperBuilder& threadId(int32_t tid)
    {
        _threadId = tid;
        return *this;
    }

    EntityWrapperBuilder& entity(const std::shared_ptr<IEntity> &entity)
    {
        _entity = entity;
        return *this;
    }

    //注意添加时需要添加 {xx, xx} 包裹
    EntityWrapperBuilder& depend(const std::initializer_list<std::shared_ptr<EntityWrapper>> &depends)
    {
        for(const auto& dep : depends)
        {
            _dependEntities.push_front(dep);
        }
        return *this;
    }

    //注意添加时需要添加 {xx, xx} 包裹
    EntityWrapperBuilder& next(const std::initializer_list<std::shared_ptr<EntityWrapper>> &nexts)
    {
        for(const auto& nex : nexts)
        {
            _nextEntities.push_front(nex);
        }
        return *this;
    }

    std::shared_ptr<EntityWrapper> build();

private:
    int32_t                     _threadId   = -1;                  //需要指定线程执行
    std::string                 _name;
    std::shared_ptr<IEntity>    _entity;

    //当前entity的下游entity， 依赖此entity的节点集合
    std::forward_list<std::shared_ptr<EntityWrapper>> _nextEntities;

    //当前entity的上游entity， 执行此entity所依赖的节点集合
    std::forward_list<std::shared_ptr<EntityWrapper>> _dependEntities;
};


}