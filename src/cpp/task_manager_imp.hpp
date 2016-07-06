//
//  task_manager_imp.hpp
//  gearsbox
//
//  Created by dyno on 7/6/16.
//
//

#ifndef task_manager_imp_hpp
#define task_manager_imp_hpp

#include <stdio.h>
#include "task_manager_gen.hpp"

namespace gearsbox {
    
class TaskGen;

class TaskManagerImp:public TaskManagerGen {
public:
    virtual ~TaskManagerImp() {}
    
    static std::shared_ptr<TaskManagerGen> instance();
    
    virtual void addTask(const std::shared_ptr<TaskGen> & task);
    
    virtual void addDelayTask(int64_t delay, int64_t repeated);
};
    
}  // namespace gearsbox


#endif /* task_manager_imp_hpp */
