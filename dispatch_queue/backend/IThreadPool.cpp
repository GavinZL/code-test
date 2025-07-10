#include "IThreadPool.h"
#include "SerialThreadPool.h"
#include "ParallelThreadPool.h"
#include <memory>
namespace queue 
{
    const std::shared_ptr<IThreadPool>& IThreadPool::serialThreadPool()
    {
        static std::shared_ptr<IThreadPool> sSerialThreadPool = 
            std::static_pointer_cast<IThreadPool>(std::make_shared<SerialThreadPool>());
        return sSerialThreadPool;
    }

    const std::shared_ptr<IThreadPool>& IThreadPool::parallelThreadPool()
    {
        static std::shared_ptr<IThreadPool> sGlobalThreadPool = 
            std::static_pointer_cast<IThreadPool>( std::make_shared<ParallelThreadPool>());
        return sGlobalThreadPool;
    }
    
}