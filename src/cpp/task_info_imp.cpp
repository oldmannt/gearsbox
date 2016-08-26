//
//  task_info_imp.cpp
//  gearsbox
//
//  Created by dyno on 8/10/16.
//
//

#include "task_info_imp.hpp"

using namespace gearsbox;


std::string TaskInfoImp::getValue(const std::string & key){
    STR_MAP_VALUE::iterator find(m_str_values.find(key));
    if (find==m_str_values.end())
        return "";
    return find->second;
}


void TaskInfoImp::setValue(const std::string & key, const std::string & value){
    m_str_values[key]=value;
}

int64_t TaskInfoImp::getIValue(const std::string & key){
    STR_MAP_IVALUE::iterator find(m_i64_values.find(key));
    if (find==m_i64_values.end())
        return 0;
    return find->second;
}

double TaskInfoImp::getFValue(const std::string & key){
    STR_MAP_FVALUE::iterator find(m_f64_values.find(key));
    if (find==m_f64_values.end())
        return 0.0;
    return find->second;
}

void TaskInfoImp::setIValue(const std::string & key, int64_t value){
    m_i64_values[key] = value;
}

void TaskInfoImp::setFValue(const std::string & key, double value){
    m_f64_values[key] = value;
}