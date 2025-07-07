#include "EntityWrapperBuilder.h"

namespace task
{

std::shared_ptr<EntityWrapper> EntityWrapperBuilder::build()
{
    std::shared_ptr<EntityWrapper> entWrapper = std::make_shared<EntityWrapper>(_name, _entity);
    entWrapper->setRunThread(_threadId);
    entWrapper->setPrevDepend(_dependEntities);
    entWrapper->setNextDepend(_nextEntities);
    entWrapper->resetState();

    return entWrapper;
}


}