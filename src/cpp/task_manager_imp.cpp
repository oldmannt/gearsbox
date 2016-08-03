//
//  task_manager_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/6/16.
//
//

#include "task_manager_imp.hpp"
#include "task_excuser_gen.hpp"
#include "macro.h"

using namespace gearsbox;

static std::shared_ptr<TaskManagerImp> s_ptr = std::make_shared<TaskManagerImp>();
std::shared_ptr<TaskManagerGen> TaskManagerGen::instance(){
    return s_ptr;
}

static void close_idel_cb(uv_handle_t* handle) {
    delete handle;
}

static void idle_cb(uv_idle_t* handle) {
    s_ptr->process();
}

void TaskManagerImp::process(){
    uint16_t now = uv_now(uv_default_loop());
    
    // if task_id == -1, it will be remove
    MAP_TASK::iterator it_task(m_map_task.begin());
    for (; it_task!=m_map_task.end(); ) {
        std::shared_ptr<TaskInfo> info = it_task->first;
        if (info->tarsk_id != -1){
            ++it_task;
            continue;
        }
        
        m_map_task.erase(++it_task);
    }
    
    it_task = m_map_task.begin();
    for (; it_task!=m_map_task.end(); ++it_task) {
        std::shared_ptr<TaskInfo> info = it_task->first;
        if (nullptr==info){
            info->tarsk_id = -1;
            continue;
        }
        
        if (now - info->elapsed < info->delay){
            continue;
        }
        
        info->elapsed = now;
        
        std::shared_ptr<TaskExcuserGen> task_excuser = it_task->second;
        if (task_excuser==nullptr)
            this->listTaskExcuser(info);
        else{
            task_excuser->excuse(*info);
        }
        
        if (--info->repeated < 0)
            info->tarsk_id = -1;
    }
}

void TaskManagerImp::listTaskExcuser(std::shared_ptr<TaskInfo> info){
    SET_TASKEXCUSER::iterator it_ecuser(m_set_taskexcuser.begin());
    for (; it_ecuser!=m_set_taskexcuser.end(); ++it_ecuser) {
        std::shared_ptr<TaskExcuserGen> task_excuser = *it_ecuser;
        if (nullptr==task_excuser)
            continue;
        task_excuser->excuse(*info);
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
    std::shared_ptr<TaskInfo> info = std::make_shared<TaskInfo>(task_id, delay, repeated, uv_now(uv_default_loop()));
    if (delay<0){
        listTaskExcuser(info);
        return;
    }
    m_map_task[info] = task;
}

void TaskManagerImp::addTaskInfo(const TaskInfo & task, const std::shared_ptr<TaskExcuserGen> & task_excuser){
    std::shared_ptr<TaskInfo> info = std::make_shared<TaskInfo>(task.tarsk_id, task.delay, task.repeated, uv_now(uv_default_loop()));
    m_map_task[info] = task_excuser;
}

void TaskManagerImp::addTaskExcuser(const std::shared_ptr<TaskExcuserGen> & task){
    SET_TASKEXCUSER::iterator find(m_set_taskexcuser.find(task));
    CHECK_RT(find == m_set_taskexcuser.end(),"addTaskExcuser failed ");
    
    m_set_taskexcuser.insert(task);
}
