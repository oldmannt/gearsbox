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
#include "task_manager_gen.hpp"
#include "task_info.hpp"
#include "uv.h"

namespace gearsbox {
    
class TaskExcuserGen;

class TaskManagerImp:public TaskManagerGen {
public:
    virtual ~TaskManagerImp();
    TaskManagerImp();
    
    static std::shared_ptr<TaskManagerGen> instance();
    
    virtual void addTask(int64_t task_id, int64_t delay, int64_t repeated, const std::shared_ptr<TaskExcuserGen> & task);
    virtual void addTaskInfo(const TaskInfo & task, const std::shared_ptr<TaskExcuserGen> & task_excuser);
    virtual void addTaskExcuser(const std::shared_ptr<TaskExcuserGen> & task);
    
    void process();
    
private:
    typedef std::map<std::shared_ptr<TaskInfo>, std::shared_ptr<TaskExcuserGen>> MAP_TASK;
    typedef std::set<std::shared_ptr<TaskExcuserGen>> SET_TASKEXCUSER;
    
    MAP_TASK m_map_task;
    SET_TASKEXCUSER m_set_taskexcuser;
    
    uv_idle_t m_idle_handle;
    
    void listTaskExcuser(std::shared_ptr<TaskInfo> info);
};
    
}  // namespace gearsbox


#endif /* task_manager_imp_hpp */
