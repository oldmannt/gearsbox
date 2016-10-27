//
//  async_task_pool.hpp
//  gearsbox
//
//  Created by dyno on 10/26/16.
//
//

#ifndef async_task_pool_hpp
#define async_task_pool_hpp

#include <memory>
#include <functional>
#include <map>

#include "queue_thread.hpp"
namespace gearsbox {
class AsyncTaskPool{
public:
    enum class TaskType{
        FILE,
        NETWORK,
        OTHER,
    };
    AsyncTaskPool(){
    }
    ~AsyncTaskPool(){
        m_map_threads.clear();
    }
    
    static std::shared_ptr<AsyncTaskPool> instance();
    static void destory();
    
    void stopTask(TaskType type);
    void enqueue(TaskType type, const std::function<void()> task, const std::function<void()> after);
    
private:
    static std::shared_ptr<AsyncTaskPool> s_instance;
    
    typedef std::map<TaskType, std::shared_ptr<QueueThread>> MapThread;
    MapThread m_map_threads;
    std::shared_ptr<QueueThread> getThread(TaskType type);
};
}
#endif /* async_task_pool_hpp */
