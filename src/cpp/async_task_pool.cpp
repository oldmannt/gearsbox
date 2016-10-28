//
//  async_task_pool.cpp
//  gearsbox
//
//  Created by dyno on 10/26/16.
//
//

#include "async_task_pool.hpp"
#include "queue_thread.hpp"
#include "macro.h"

using namespace gearsbox;

std::shared_ptr<AsyncTaskPool> AsyncTaskPool::s_instance = nullptr;

std::shared_ptr<AsyncTaskPool> AsyncTaskPool::instance(){
    static bool _initialize = false;
    if (s_instance==nullptr && !_initialize){
        s_instance = std::make_shared<AsyncTaskPool>();
        _initialize = true;
    }
    return s_instance;
}

void AsyncTaskPool::destory(){
    s_instance = nullptr;
}

void AsyncTaskPool::stopTask(gearsbox::AsyncTaskPool::TaskType type){
    auto thread = this->getThread(type);
    CHECK_RT(thread!=nullptr, "type:%d queue thread null", (int)type);
    thread->clear();
    m_map_threads[type] = nullptr;
}

void AsyncTaskPool::enqueue(gearsbox::AsyncTaskPool::TaskType type, const std::function<void ()> task, const std::function<void ()> after){
    auto thread = this->getThread(type);
    CHECK_RT(thread!=nullptr, "type:%d queue thread null", (int)type);
    thread->enqueue(task, after);
}

std::shared_ptr<QueueThread> AsyncTaskPool::getThread(TaskType type){
    auto iter = m_map_threads.find(type);
    
    if (iter == m_map_threads.end() || iter->second == nullptr) {
        auto thread = std::make_shared<QueueThread>();
        m_map_threads[type] = thread;
        return thread;
    }
    
    return iter->second;
}
