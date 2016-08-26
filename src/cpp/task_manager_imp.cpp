//
//  task_manager_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/6/16.
//
//

#include "task_manager_imp.hpp"
#include "task_excuser_gen.hpp"
#include "task_info_imp.hpp"
#include "macro.h"

using namespace gearsbox;

static std::shared_ptr<TaskManagerImp> s_ptr = std::make_shared<TaskManagerImp>();
std::shared_ptr<TaskManagerGen> TaskManagerGen::instance(){
    return s_ptr;
}

std::shared_ptr<TaskInfoGen> TaskManagerGen::create(int64_t task_id, int64_t delay, int32_t repeated){
    return std::make_shared<TaskInfoImp>(task_id,delay,repeated);
}

static void close_idel_cb(uv_handle_t* handle) {
    delete handle;
}

static void idle_cb(uv_idle_t* handle) {
    s_ptr->process();
}

void TaskManagerImp::process(){
    uint64_t now = uv_now(uv_default_loop());
    
    MAP_TASK::iterator it_task = m_map_task.begin();
    for (; it_task!=m_map_task.end(); ) {
        std::shared_ptr<TaskInfoGen> info = it_task->first;
        if (nullptr==info || -1 == info->getTaskId()){
            m_map_task.erase(it_task++);
            continue;
        }
        
        if (now - info->getAssignTick() < info->getDelay()){
            ++it_task;
            continue;
        }
        
        info->setRepeated(info->getRepeated()-1);
        std::shared_ptr<TaskExcuserGen> task_excuser = it_task->second;
        if (task_excuser==nullptr)
            this->listTaskExcuser(info);
        else{
            task_excuser->excuse(info);
        }
        
        if (info->getRepeated() < 0)
            info->setTaskId(-1);
        ++it_task;
    }
}

void TaskManagerImp::listTaskExcuser(std::shared_ptr<TaskInfoGen> info){
    SET_TASKEXCUSER::iterator it_ecuser(m_set_taskexcuser.begin());
    for (; it_ecuser!=m_set_taskexcuser.end(); ++it_ecuser) {
        std::shared_ptr<TaskExcuserGen> task_excuser = *it_ecuser;
        if (nullptr==task_excuser)
            continue;
        task_excuser->excuse(info);
    }
}

TaskManagerImp::TaskManagerImp(){
    uv_idle_init(uv_default_loop(), &m_idle_handle);
    uv_idle_start(&m_idle_handle, idle_cb);
}

TaskManagerImp::~TaskManagerImp(){
    uv_idle_stop(&m_idle_handle);
    uv_close((uv_handle_t*) &m_idle_handle,close_idel_cb);
}

void TaskManagerImp::addTask(int64_t task_id, int64_t delay, int64_t repeated, const std::shared_ptr<TaskExcuserGen> & task){
    std::shared_ptr<TaskInfoGen> info = TaskManagerGen::create(task_id, delay, repeated);
    this->addTaskInfo(info, task);
}

void TaskManagerImp::addTaskI(int64_t task_id, const std::shared_ptr<TaskExcuserGen> & task){
    this->addTask(task_id, 0, 0, task);
}

void TaskManagerImp::addTaskInfo(const std::shared_ptr<TaskInfoGen> & task, const std::shared_ptr<TaskExcuserGen> & task_excuser){
    if (task == nullptr)
        return;
    task->setAssignTick(uv_now(uv_default_loop()));
    if (task->getDelay()<0){
        listTaskExcuser(task);
        return;
    }
    m_map_task[task] = task_excuser;
}

void TaskManagerImp::addTaskExcuser(const std::shared_ptr<TaskExcuserGen> & task){
    SET_TASKEXCUSER::iterator find(m_set_taskexcuser.find(task));
    CHECK_RT(find == m_set_taskexcuser.end(),"addTaskExcuser failed ");
    
    m_set_taskexcuser.insert(task);
}

void TaskManagerImp::removeTask(int64_t task_id){
    MAP_TASK::iterator it_task = m_map_task.begin();
    for (; it_task!=m_map_task.end(); ) {
        std::shared_ptr<TaskInfoGen> info = it_task->first;
        if (nullptr==info && task_id == info->getTaskId()){
            m_map_task.erase(it_task++);
            continue;
        }
        
        ++it_task;
    }

}
