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
#include "thread_checker.hpp"
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

    void process();
    
private:
    typedef std::map<std::shared_ptr<TaskInfoGen>, std::shared_ptr<TaskExcuserGen>> MAP_TASK;
    typedef std::set<std::shared_ptr<TaskExcuserGen>> SET_TASKEXCUSER;
    
    ThreadChecker m_thread_checker;
    MAP_TASK m_map_task;
    SET_TASKEXCUSER m_set_taskexcuser;
    
    uv_idle_t m_idle_handle;
    std::mutex m_mt_task;
    
    void listTaskExcuser(std::shared_ptr<TaskInfoGen> info);
};
    
}  // namespace gearsbox


#endif /* task_manager_imp_hpp */
