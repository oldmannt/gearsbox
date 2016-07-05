//
//  PlatformUtilityImp.cpp
//  gearsbox
//
//  Created by dyno on 6/12/16.
//
//

#include "platform_utility_imp.hpp"

using namespace gearsbox;

std::shared_ptr<PlatformUtilityGen> PlatformUtilityGen::instance(){
    static std::shared_ptr<PlatformUtilityGen> s_ptr = std::make_shared<PlatformUtilityImp>();
    return s_ptr;
}

void PlatformUtilityImp::setPlatofrmExcutor(const std::shared_ptr<PlatformExecutorGen> & excuser){
    m_executor = excuser;
}

std::shared_ptr<PlatformExecutorGen> PlatformUtilityImp::getExcutor(){
    return m_executor;
}