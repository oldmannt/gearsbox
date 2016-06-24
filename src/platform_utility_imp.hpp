//
//  PlatformUtilityImp.hpp
//  gearsbox
//
//  Created by dyno on 6/12/16.
//
//

#pragma once

#include "platform_utility_gen.hpp"
#include "platform_executor_gen.hpp"

namespace gearsbox {
    
   
    class PlatformUtilityImp: public PlatformUtilityGen {
    public:
        virtual ~PlatformUtilityImp() {
            m_executor = nullptr;
        }
        
        static std::shared_ptr<PlatformUtilityGen> instance();
        
        virtual void setPlatofrmExcutor(const std::shared_ptr<PlatformExecutorGen> & excuser);
        virtual std::shared_ptr<PlatformExecutorGen> getExcutor();
        
    private:
        std::shared_ptr<PlatformExecutorGen> m_executor;
    };
    
}  // namespace gearsbox