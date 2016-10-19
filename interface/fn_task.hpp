//
//  fn_task.hpp
//  gearsbox
//
//  Created by dyno on 10/13/16.
//
//

#ifndef fn_task_hpp
#define fn_task_hpp

#include <functional>
#include "task_excuser_gen.hpp"


namespace gearsbox {
    
    // a helper class to turn the `TaskInfoGen` api into a std::function based one
    class FnTask final : public TaskExcuserGen {
    public:
        FnTask(std::function<void()> run_me): m_fn {std::move(run_me)} {
        }
        virtual void excuse(const std::shared_ptr<TaskInfoGen> & info) override{
            m_fn();
        }
    private:
        std::function<void()> m_fn;
    };
}

#endif /* fn_task_hpp */
