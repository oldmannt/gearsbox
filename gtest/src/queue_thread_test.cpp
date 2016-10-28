//
//  queue_thread_test.cpp
//  gearsbox
//
//  Created by dyno on 10/25/16.
//
//

#include <chrono>
#include <sstream>
#include "gtest/gtest.h"
#include "async_task_pool.hpp"
#include "fn_task.hpp"
#include "task_manager_gen.hpp"
#include "macro.h"
#include "utils.hpp"

#ifdef GEARSBOX_TEST
using namespace gearsbox;
// Step 2. Use the TEST macro to define your tests.
// Tests factorial of negative numbers.

class Foo {
public:
    Foo():_value(0){
    }
    ~Foo(){
    }
    
    void work(int arg, std::shared_ptr<void> func){
        _value += arg;
        G_LOG_C(LOG_INFO, "work: %x, vaule:%d", this, _value);
        
        auto task = std::static_pointer_cast<FnTask>(func);
        TaskManagerGen::instance()->addTaskI((int64_t)this, task);
        //TaskManagerGen::instance()->addMainThreadTask((int64_t)this, nullptr);
    }
    void after( std::shared_ptr<void> func){
        ++_value;
        G_LOG_C(LOG_INFO, "after: %x, vaule:%d, %d", this, _value, nowMilli());
        AsyncTaskPool::instance()->stopTask(AsyncTaskPool::TaskType::OTHER);
        //uv_print_active_handles(uv_default_loop(), stdout);
        //uv_stop(uv_default_loop());
        
        if (func!=nullptr){
            auto task = std::static_pointer_cast<FnTask>(func);
            task->excuse(nullptr);
        }
    }
    
    int _value;
    //std::shared_ptr<QueueThread> _queue;
};

std::function<void()> getFunc(const std::string& flag){
    return [flag](){
        
        G_LOG_C(LOG_INFO, "getFunc:%s now:%d", flag.c_str(), nowMilli());
    };
}

std::function<void()> getIncFunc(const std::string& flag, int* value, int inc){
    return [flag, value, inc]()mutable{
        *value+=inc;
        //G_LOG_C(LOG_INFO, "getIncFunc:%s value:%d now:%d", flag.c_str(), *value, nowMilli());
    };
}

Foo foo;
TEST(queue_thread, test) {
    
    int value = 0;
    int count = 1;
    for (int i=0; i<count; ++i) {
        std::ostringstream oss;
        oss << "inc_fun" << i;
        auto inc_fun = getIncFunc(oss.str().c_str(), &value, 1);
        oss << "_after";
        auto after_inc = getFunc(oss.str().c_str());
        AsyncTaskPool::instance()->enqueue(AsyncTaskPool::TaskType::OTHER, inc_fun, nullptr);
        //usleep(5000);
        //EXPECT_EQ(value, i+1);
    }
    
    usleep(5000*count);
    EXPECT_EQ(value, count);
    
    /*
    int arg = 1;
    
    std::shared_ptr<FnTask> func = std::make_shared<FnTask>(getFunc("work1'arg"));
    std::shared_ptr<FnTask> func1 = std::make_shared<FnTask>(getFunc("work1'after"));
    
    std::function<void()> task = std::bind(&Foo::work, std::ref(foo), arg, func);
    std::function<void()> after = std::bind(&Foo::after, std::ref(foo), nullptr);
    AsyncTaskPool::instance()->enqueue(AsyncTaskPool::TaskType::OTHER, task, after);
    
    auto u1 = nowMilli();
    usleep(2000);
    G_LOG_C(LOG_INFO, "after sleep: %d size of long long:%d", nowMilli()-u1, sizeof(u1));
    
    EXPECT_EQ(foo._value, arg);
    */
    
    //uv_print_active_handles(uv_default_loop(), stdout);

}

#endif
