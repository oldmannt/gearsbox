//
//  queue_thread.cpp
//  gearsbox
//
//  Created by dyno on 10/24/16.
//
//

#include "queue_thread.hpp"
#include "macro.h"

using namespace gearsbox;



void thread(void* data){
    QueueThread* task_queue = (QueueThread*)data;
    if (!task_queue)
        return;
    //G_LOG_C(LOG_INFO,"begin thread %x", data);
    task_queue->work();
    //G_LOG_C(LOG_INFO,"end thread %x", data);
}

void asyncTaskCB(uv_async_t *handle){
    QueueData* data = (QueueData*)handle->data;
    std::shared_ptr<QueueData> pdata(data);
    if (pdata && pdata->_after_task!=nullptr)
        pdata->_after_task();
    uv_close((uv_handle_t*)pdata->_async.get(), nullptr);
}

QueueThread::QueueThread():m_stop(false){
    m_self_thread = uv_thread_self();
    uv_cond_init(&m_condition);
    uv_mutex_init(&m_mutex);
    uv_thread_create(&m_thread, thread, this);
}

QueueThread::~QueueThread(){
    {
        uv_mutex_lock(&m_mutex);
        std::shared_ptr<uv_mutex_t> auto_unlock(&m_mutex, uv_mutex_unlock);
        m_stop = true;
        while (m_queue.size()>0) {
            m_queue.pop();
        }
    }
    uv_cond_broadcast(&m_condition);
    uv_thread_join(&m_thread);
    
    uv_mutex_destroy(&m_mutex);
    uv_cond_destroy(&m_condition);
}

void QueueThread::clear(){
    uv_mutex_lock(&m_mutex);
    std::shared_ptr<uv_mutex_t> auto_unlock(&m_mutex, uv_mutex_unlock);
    while (m_queue.size()>0) {
        m_queue.pop();
    }
}

void QueueThread::enqueue(const std::function<void()>& task,const std::function<void()>& after_task){
    
    {
        uv_mutex_lock(&m_mutex);
        std::shared_ptr<uv_mutex_t> auto_unlock(&m_mutex, uv_mutex_unlock);
        
        QueueData data = {task, after_task, std::make_shared<uv_async_t>()};
        uv_async_init(uv_default_loop(), data._async.get(), asyncTaskCB);
        m_queue.emplace(std::move(data));
    }
    uv_cond_signal(&m_condition);
}

void QueueThread::work(){
    CHECK_RT(!this->checkSameThread(), "save thread call QueueThread::work");

    while (true) {
        QueueData data;
        {
            uv_mutex_lock(&m_mutex);
            std::shared_ptr<uv_mutex_t> auto_unlock(&m_mutex, uv_mutex_unlock);
            
            if (m_queue.empty())
                uv_cond_wait(&m_condition, &m_mutex);
            if (m_stop) return;
            data = std::move(m_queue.front());
            m_queue.pop();
        }
        QueueData* async_data = new QueueData;
        *async_data = std::move(data);
        if (async_data->_task!=nullptr){
            async_data->_task();
        }
        
        async_data->_async->data = async_data;
        uv_async_send(async_data->_async.get());
        /*
        if (async_data->_after_task!=nullptr){
         
        }
        else{
            std::shared_ptr<QueueData> pdata(async_data); // auto delete
            uv_close((uv_handle_t *)async_data->_async.get(), nullptr);
        }*/

    }
}

bool QueueThread::checkSameThread(){
    uv_thread_t this_thread = uv_thread_self();
    return uv_thread_equal(&this_thread, &m_self_thread)!=0;
}
