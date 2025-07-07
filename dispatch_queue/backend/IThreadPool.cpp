#include "IThreadPool.h"
#include "ExclusiveThreadPool.h"
#include "ParallelThreadPool.h"
#include <memory>
namespace queue 
{
    const std::shared_ptr<IThreadPool>& IThreadPool::exculsiveThreadPool()
    {
        static std::shared_ptr<IThreadPool> sExclusiveThreadPool = 
            std::static_pointer_cast<IThreadPool>(std::make_shared<ExclusiveThreadPool>());
        return sExclusiveThreadPool;
    }

    const std::shared_ptr<IThreadPool>& IThreadPool::globalThreadPool()
    {
        static std::shared_ptr<IThreadPool> sGlobalThreadPool = 
            std::static_pointer_cast<IThreadPool>( std::make_shared<ParallelThreadPool>());
        return sGlobalThreadPool;
    }
    
}