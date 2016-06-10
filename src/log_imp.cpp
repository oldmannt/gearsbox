//
//  gearbox_log_imp.cpp
//  gearsbox
//
//  Created by dyno on 5/17/16.
//
//

#include "log_imp.hpp"
#include "ILog.h"
#include <vector>
#include <string>

using namespace gearsbox;

const std::string exclude_path(const std::string& msg)
{
    // depend on source file is the last file in the msg
    const char* src_file = 0;
    const char* src_first = 0;
    const char* ori_msg = msg.c_str();
    for (const char* p=ori_msg+msg.length(); p!=ori_msg; --p) {
        if (src_file == 0 &&('/' == *p || '\\' == *p)){
            src_file = p+1;
        }
        if (src_file!=0 && *p == ' '){
            src_first = p+1;
            break;
        }
    }
    if (src_file == 0 || src_file == ori_msg)
        return msg;
    
    std::string newmsg(msg);
    newmsg.replace(src_first-ori_msg, std::string::npos, src_file);
    return newmsg;
}

std::shared_ptr<LogGen> LogGen::instance(){
    static std::shared_ptr<LogImp> s_gearbox_log = std::make_shared<LogImp>();
    return s_gearbox_log;
}

bool LogImp::initialize(int32_t output, const std::string & param){
    return LOG_OK == g_loginit(output, param.c_str());
}

void LogImp::log(int32_t output, int32_t lev, const std::string &msg){
    g_logouts(output, lev, exclude_path(msg).c_str());
}

void LogImp::logerrf(const std::string & msg){
    g_logouts(LOG_CONSOLE|LOG_FILE, LOG_ERROR ,exclude_path(msg).c_str());
}

void LogImp::loginfo(const std::string & msg){
    g_logouts(LOG_CONSOLE, LOG_INFO, exclude_path(msg).c_str());
}


