//
//  task_manager_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/6/16.
//
//

#include "task_manager_imp.hpp"
#include "task_gen.hpp"

using namespace gearsbox;

std::shared_ptr<TaskManagerGen> TaskManagerGen::instance(){
    static std::shared_ptr<TaskManagerGen> s_ptr = std::make_shared<TaskManagerImp>();
    return s_ptr;
}

void TaskManagerImp::addTask(const std::shared_ptr<TaskGen> &task){
    
}

void TaskManagerImp::addDelayTask(int64_t delay, int64_t repeated){
    
}