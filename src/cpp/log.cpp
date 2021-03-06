//
//  Log.cpp
//  USNIT
//
//  Created by dyno on 4/14/16.
//  Copyright © 2016 dyno. All rights reserved.
//

#include <stdio.h>
#include <list>
#include <string.h>
#include <stdarg.h>
#include "ILog.h"

#include "zf_log/zf_log.h"

/*
#if defined (__APPLE_CC__)
#   define ZF_LOG_USE_NSLOG
#elif defined (__ANDROID__)
#   define ZF_LOG_USE_ANDROID_LOG
#endif
#define ZF_LOG_LEVEL ZF_LOG_INFO
 */

static void fz_log_callback(const zf_log_message *msg, void* arg);

struct G_LOG_INFO {
    int init;
    int outputs;
    FILE* file;
    char file_path[512];
    zf_log_output_cb console_cb;
    zf_log_output_cb file_cb;
    
    G_LOG_INFO(){
        memset(this, 0, sizeof(G_LOG_INFO));
    }
};
G_LOG_INFO g_log_info;

static void zf_file_log(const zf_log_message* msg, void* arg){
    if (!g_log_info.file){
        g_logouts(LOG_CONSOLE, LOG_ERROR, "no file handle for log");
        return;
    }
    *msg->p = '\n';
    fwrite(msg->buf, msg->p - msg->buf + 1, 1, g_log_info.file);
    fflush(g_log_info.file);
}

static void fz_log_callback(const zf_log_message *msg, void* arg){
    // CLogMgr::Instance().zf_log(msg, arg);
    
    if (!msg || !arg)
        return;
    G_LOG_INFO* loginfo = (G_LOG_INFO*)arg;
    if (loginfo->outputs&LOG_CONSOLE && g_log_info.console_cb)
        (*g_log_info.console_cb)(msg,arg);
    if (loginfo->outputs&LOG_FILE && g_log_info.file_cb) {
        (*g_log_info.file_cb)(msg,arg);
    }
    
}

int g_addlog(int outputs, const char* param){
    if (outputs&LOG_CONSOLE){
        g_log_info.console_cb = _zf_log_global_output.callback;
    }
    else if(outputs&LOG_FILE){
        
        g_log_info.file = fopen(param, "a");
        if (!g_log_info.file){
            G_LOG_C(LOG_ERROR, "fopne file log failed:%s", param);
            return LOG_OPENFILE_FAILED;
        }
        g_log_info.file_cb = zf_file_log;
        strncpy(g_log_info.file_path, param, sizeof(g_log_info.file_path));
    }
    
    g_log_info.outputs |= outputs;
    return LOG_OK;
}

int g_loginit(int outputs, const char* param){
    memset(&g_log_info, sizeof(g_log_info),0);
    g_log_info.console_cb = _zf_log_global_output.callback;
    g_log_info.init = 1;
    int rt = g_addlog(outputs, param);
    if (LOG_OK != rt){
        return rt;
    }

    unsigned mask = ZF_LOG_PUT_STD&(~ZF_LOG_PUT_SRC)&~ZF_LOG_PUT_TAG;
    zf_log_set_output_v(mask, &g_log_info, fz_log_callback);
    return LOG_OK;
}

void g_logouts(int output, int lev, const char* msg) {
    if (g_log_info.init == 0){
        g_loginit(LOG_CONSOLE, "");
    }

    switch (lev) {
        case LOG_VERBOSE:
            ZF_LOGI("%s", msg);
            break;
        case LOG_DEBUG:
            ZF_LOGD("%s", msg);
            break;
        case LOG_INFO:
            ZF_LOGI("%s", msg);
            break;
        case LOG_WARN:
            ZF_LOGD("%s", msg);
            break;
        case LOG_ERROR:
            ZF_LOGE("%s", msg);
            break;
        case LOG_FATAL:
            ZF_LOGF("%s", msg);
            break;
            
        default:
            break;
    }

}

void g_log_lx(int output, int lev, const char* fmt, ...){
    if (g_log_info.init == 0){
        g_loginit(LOG_CONSOLE, "");
    }
    
    char buf[512] = {0};
    va_list va;
    va_start(va, fmt);
    vsnprintf(buf,sizeof(buf),fmt,va);
    va_end(va);
    g_logouts(output, lev, buf);
}

void g_logout(int output, int lev, const char *const func, const char *const file, const unsigned line, const char* fmt, ...) {
    if (g_log_info.init == 0){
        g_loginit(LOG_CONSOLE, "");
    }
    
    const char* file_s = strrchr(file, '/');
    if (!file_s){
        file_s = strrchr(file, '\\');
        if (!file_s){
            file_s = file;
        }
        else{
            file_s+= 1;
        }
    }

    char buf[512] = {0};
    int n = snprintf(buf, sizeof(buf), "%s@%s:%d ",func,file_s+1,line);
    if (n < 0) {
        n = snprintf(buf, sizeof(buf), "unkownsrc ");
    }

    va_list va;
    va_start(va, fmt);
    vsnprintf(buf+n,sizeof(buf)-n,fmt,va);
    va_end(va);
    g_logouts(output, lev, buf);
}
void g_loglev(int lev) {
    zf_log_set_output_level(lev);
}

