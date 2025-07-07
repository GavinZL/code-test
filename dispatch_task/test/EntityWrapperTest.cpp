
#include "../JobDepend/EntityWrapper.h"
#include "../JobDepend/EntityWrapperBuilder.h"
#include "../JobDepend/IEntity.h"

#include "../TaskDispatcher.hpp"

#include <cstdio>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

//clang++ -std=c++17 -I.. EntityWrapperTest.cpp ../TaskDispatcher.cpp ../TaskThread.cpp ../TaskThreadPool.cpp ../JobDepend/EntityWrapper.cpp ../JobDepend/EntityWrapperBuilder.cpp -o t

std::mutex g_mutex;

class EntityImp : public task::IEntity
{
public:
    EntityImp(const std::string &name) :_name(name)
    {

    }

    virtual void onInitialze()  override
    {

    }
    virtual void onProcess()   override
    {
        for(int i=0; i<1000000000; ++i)
        {;}
        std::lock_guard<std::mutex> lock(g_mutex);
        std::cout << "EntityImp-name:"<< _name.c_str() << ", threadid:" << std::this_thread::get_id() << "\n";
    }
    virtual void onRelease()   override
    {

    }

    //是否需要执行
    virtual bool needWorking()  override
    {
        return true;
    }

private:
    std::string _name;
};

using Dispatcher = std::shared_ptr<task::TaskDispatcher>;
using Wrapper = std::shared_ptr<task::EntityWrapper>;
void test1(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4);
void test2(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4);
void test3(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4, Wrapper& ew5);
void test4(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4, Wrapper& ew5, Wrapper& ew6);
void test5(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4, Wrapper& ew5, Wrapper& ew6);

int main(int argc, char* argv[])
{

    //1. 准备线程池
    std::shared_ptr<task::TaskDispatcher> dispatcher = std::make_shared<task::TaskDispatcher>();
    dispatcher->initalize(8);        //初始化3条线程
    dispatcher->setFixThread(0, true);
    // dispatcher->setFixThread(1, true);
    // dispatcher->setFixThread(2, true);

   //2. 创建entity
    std::shared_ptr<task::IEntity> en1 = std::make_shared<EntityImp>("1");
    std::shared_ptr<task::IEntity> en2 = std::make_shared<EntityImp>("2");
    std::shared_ptr<task::IEntity> en3 = std::make_shared<EntityImp>("3");
    std::shared_ptr<task::IEntity> en4 = std::make_shared<EntityImp>("4");
    std::shared_ptr<task::IEntity> en5 = std::make_shared<EntityImp>("5");
    std::shared_ptr<task::IEntity> en6 = std::make_shared<EntityImp>("6");

    //3. 创建entityWrapper，管理依赖
    std::shared_ptr<task::EntityWrapper> ew6 = task::EntityWrapperBuilder().name("ew6")
                                                                            .entity(en6)
                                                                            .build();

    std::shared_ptr<task::EntityWrapper> ew5 = task::EntityWrapperBuilder().name("ew5")
                                                                            .entity(en5)
                                                                            .build();

    std::shared_ptr<task::EntityWrapper> ew4 = task::EntityWrapperBuilder().name("ew4")
                                                                            .entity(en4)
                                                                            .build();

    std::shared_ptr<task::EntityWrapper> ew3 = task::EntityWrapperBuilder().name("ew3")
                                                                            .entity(en3)
                                                                            .build();

    std::shared_ptr<task::EntityWrapper> ew2 = task::EntityWrapperBuilder().name("ew2")
                                                                            .entity(en2)
                                                                            .build();

    std::shared_ptr<task::EntityWrapper> ew1 = task::EntityWrapperBuilder().name("ew1")
                                                                            .entity(en1)
                                                                            .build();

    //顺序链 1->2->3->4
    // test1(dispatcher, ew1, ew2, ew3, ew4);

    //1-2-4
    // -3-
    // test2(dispatcher, ew1, ew2, ew3, ew4);

    //1-2-4-5
    // -3---
    // test3(dispatcher, ew1, ew2, ew3, ew4, ew5);

    test4(dispatcher, ew1, ew2, ew3, ew4, ew5, ew6);

    std::this_thread::sleep_for(std::chrono::seconds(30));
    dispatcher->destroy();

    return 0;
}

//顺序链 1->2->3->4
void test1(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4)
{

    ew1->addNextDepend(ew2);
    ew2->addNextDepend(ew3);
    ew3->addNextDepend(ew4);


    //4.组装第一个task，抛给线程
    std::shared_ptr<task::Task> task = std::make_shared<task::Task>();
    task->setTaskId(1024);
    // task->setThreadId(0);
    task->setCallback([&ew1, &dispatcher](std::shared_ptr<task::Task> tsk) {
        ew1->doWork(dispatcher);
    });

    dispatcher->dispatchTask(task);
}

//  --2--
// 1      4
//  --3--
void test2(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4)
{

    ew1->addNextDepend(ew2);
    ew1->addNextDepend(ew3);
    // ew1->setRunThread(0);

    ew2->addNextDepend(ew4);
    // ew2->setRunThread(1);
    ew3->addNextDepend(ew4);
    // ew3->setRunThread(2);

    ew4->addPrevDepend(ew2);
    ew4->addPrevDepend(ew3);
    // ew4->setRunThread(0);

    //4.组装第一个task，抛给线程
    std::shared_ptr<task::Task> task = std::make_shared<task::Task>();
    task->setTaskId(1024);
    // task->setThreadId(0);
    task->setCallback([&ew1, &dispatcher](std::shared_ptr<task::Task> tsk) {
        ew1->doWork(dispatcher);
    });

    dispatcher->dispatchTask(task);

}

//1-2-4-
// -3---5
void test3(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4, Wrapper& ew5)
{
    ew1->addNextDepend(ew2);
    ew1->addNextDepend(ew3);
    // ew1->setRunThread(0);

    ew2->addNextDepend(ew4);
    // ew2->setRunThread(1);
    ew3->addNextDepend(ew5);
    // ew3->setRunThread(2);

    ew4->addNextDepend(ew5);

    ew5->addPrevDepend(ew4);
    ew5->addPrevDepend(ew3);
    // ew4->setRunThread(0);

    //4.组装第一个task，抛给线程
    std::shared_ptr<task::Task> task = std::make_shared<task::Task>();
    task->setTaskId(1024);
    // task->setThreadId(0);
    task->setCallback([&ew1, &dispatcher](std::shared_ptr<task::Task> tsk) {
        ew1->doWork(dispatcher);
    });

    dispatcher->dispatchTask(task);
}


//A--       --D--
//     C            F
//B--       --E-- 
void test4(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4, Wrapper& ew5, Wrapper& ew6)
{

    ew1->addNextDepend(ew3);
    ew2->addNextDepend(ew3);

    ew3->addPrevDepend(ew1);
    ew3->addPrevDepend(ew2);
    ew3->addNextDepend(ew4);
    ew3->addNextDepend(ew5);

    ew4->addNextDepend(ew6);
    ew5->addNextDepend(ew6);

    ew6->addPrevDepend(ew4);
    ew6->addPrevDepend(ew5);


    //4.组装task，将ew1抛给线程
    std::shared_ptr<task::Task> task = std::make_shared<task::Task>();
    task->setTaskId(1024);
    // task->setThreadId(0);
    task->setCallback([&ew1, &dispatcher](std::shared_ptr<task::Task> tsk) {
        ew1->doWork(dispatcher);
    });

    dispatcher->dispatchTask(task);

    //5.组装task，将ew2抛给线程
    task = std::make_shared<task::Task>();
    task->setTaskId(1025);
    // task->setThreadId(0);
    task->setCallback([&ew2, &dispatcher](std::shared_ptr<task::Task> tsk) {
        ew2->doWork(dispatcher);
    });

    dispatcher->dispatchTask(task);
}
void test5(const Dispatcher& dispatcher, Wrapper& ew1, Wrapper& ew2, Wrapper& ew3, Wrapper& ew4, Wrapper& ew5, Wrapper& ew6)
{

}