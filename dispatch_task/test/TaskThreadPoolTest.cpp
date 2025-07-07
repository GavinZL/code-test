
#include "../TaskThread.hpp"
#include "../TaskThreadPool.hpp"


int main(int argc, char* argv[])
{

    task::TaskThreadPool pool;
    pool.initialize();


    std::this_thread::sleep_for(std::chrono::seconds(3));

    pool.destory();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}