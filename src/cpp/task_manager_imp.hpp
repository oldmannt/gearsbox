//
//  task_manager_imp.hpp
//  gearsbox
//
//  Created by dyno on 7/6/16.
//
//

#ifndef task_manager_imp_hpp
#define task_manager_imp_hpp

#include <map>
#include <set>
#include <mutex>
#include <queue>
#include "task_manager_gen.hpp"
#include "task_info_gen.hpp"
#include "uv.h"

namespace gearsbox {
    
class TaskExcuserGen;

class TaskManagerImp:public TaskManagerGen {
public:
    virtual ~TaskManagerImp();
    TaskManagerImp();
       
    virtual void addTask(int64_t task_id, int64_t delay, int32_t repeated, const std::shared_ptr<TaskExcuserGen> & task);
    virtual void addTaskI(int64_t task_id, const std::shared_ptr<TaskExcuserGen> & task);
    virtual void addTaskInfo(const std::shared_ptr<TaskInfoGen> & task, const std::shared_ptr<TaskExcuserGen> & task_excuser);
    virtual void addTaskExcuser(const std::shared_ptr<TaskExcuserGen> & task);
    virtual void removeTask(int64_t task_id);
    
    virtual void addMainThreadTask(const std::shared_ptr<TaskExcuserGen> & task, const std::shared_ptr<TaskInfoGen> & param);
    void process();
    
private:
    typedef std::map<std::shared_ptr<TaskInfoGen>, std::shared_ptr<TaskExcuserGen>> MAP_TASK;
    typedef std::set<std::shared_ptr<TaskExcuserGen>> SET_TASKEXCUSER;
    
    MAP_TASK m_map_task;
    SET_TASKEXCUSER m_set_taskexcuser;
    
    uv_idle_t m_idle_handle;
    
    std::mutex m_mt_task;
    std::queue<std::shared_ptr<TaskExcuserGen>> m_queue_mt_excuser;
    std::queue<std::shared_ptr<TaskInfoGen>> m_queue_mt_info;
    
    void listTaskExcuser(std::shared_ptr<TaskInfoGen> info);
};
    
}  // namespace gearsbox


#endif /* task_manager_imp_hpp */
