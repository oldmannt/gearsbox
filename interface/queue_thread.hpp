//
//  queue_thread.hpp
//  gearsbox
//
//  Created by dyno on 10/24/16.
//
//

#ifndef queue_thread_hpp
#define queue_thread_hpp

#include <functional>
#include <queue>

#include "uv.h"

namespace gearsbox {

struct QueueData{
    ~QueueData(){
        _async = nullptr;
    }
    std::function<void()> _task;
    std::function<void()> _after_task;
    std::shared_ptr<uv_async_t> _async;
};
class QueueThread {
public:
    
    QueueThread();
    ~QueueThread();
    
    void clear();
    void enqueue(const std::function<void()>& task,const std::function<void()>& after_task);
    void work();
    
private:
    
    uv_thread_t m_thread;
    uv_mutex_t m_mutex;
    uv_cond_t m_condition;
    uv_thread_t m_self_thread;
    std::queue<QueueData> m_queue;
    bool m_stop;
    
    bool checkSameThread();
};
    
}
#endif /* queue_thread_hpp */
