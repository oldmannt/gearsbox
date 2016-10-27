//
//  work_thread.cpp
//  gearsbox
//
//  Created by dyno on 10/15/16.
//
//

#include "work_thread.hpp"
using namespace gearsbox;

void workThreadCB(uv_work_t* req){
    WorkThread* work_thread = (WorkThread*)req->data;
    if (!work_thread)
        return;
    
    work_thread->work();
}

void afterWokdCB(uv_work_t* req, int status){
    WorkThread* work_thread = (WorkThread*)req->data;
    if (!work_thread)
        return;
    
    work_thread->afterWork();
}

void asyncWorkCB(uv_async_t *handle){
    
}

void WorkThread::start(){
    
    m_work.data = (void*)this;
    uv_queue_work(uv_default_loop(), &m_work, workThreadCB, afterWokdCB);
}

void WorkThread::work(){
    m_fn();
}

void WorkThread::afterWork(){
    m_rt();
}

// only work when the thread is not yet to start
void WorkThread::cancel(){
    uv_cancel((uv_req_t*)&m_work);
}
