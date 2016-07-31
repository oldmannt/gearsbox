//
//  TimerImp.cpp
//  gearsbox
//
//  Created by dyno on 6/8/16.
//
//

#include "TimerImp.hpp"
#include "ILog.h"
#include "task_info.hpp"
#include <unordered_map>

using namespace gearsbox;

std::shared_ptr<TimerGen> TimerGen::create(int64_t timeout, int32_t repeat_times, const std::shared_ptr<TaskExcuserGen> & hander){
    return std::make_shared<TimerImp>(timeout, repeat_times, hander);
}

typedef std::unordered_map<uv_timer_t*, TimerImp*> MapTimer;
static MapTimer s_timerMap;
static void timer_cb(uv_timer_t* handle) {
    if (!handle || !handle->data){
        return;
    }
    
    TimerImp* timerimp = (TimerImp*)handle->data;
    timerimp->timerCallback();
}

static void close_timer_cb(uv_handle_t* handle) {
    delete handle;
}

TimerImp::TimerImp(int64_t timeout, int32_t repeat, std::shared_ptr<TaskExcuserGen> handler)
:m_timeout(timeout),
m_timePassed(0),
m_repeatTimes(repeat),
m_repeated(0),
m_running(false),
m_handler(handler){
    m_timer = new uv_timer_t();
    m_timer->data = this;
    uv_timer_init(uv_default_loop(), m_timer);
}

TimerImp::~TimerImp() {
    uv_close((uv_handle_t*)m_timer, close_timer_cb);
    m_handler = nullptr;
}

void TimerImp::timerCallback(){
    m_timePassed += m_timeout;
    ++m_repeated;
    
    TaskInfo info(-1, m_timeout, m_repeated, m_repeated);
    if (m_handler)
        m_handler->excuse(info);
    
    if (m_repeatTimes<0 || m_repeated<m_repeatTimes){
        return;
    }
    
    uv_timer_stop(m_timer);
    m_running = false;
}

bool TimerImp::start(){
    uint64_t is_repeat = m_repeatTimes==0?0:m_timeout;
    if (0 != uv_timer_start(m_timer, timer_cb, m_timeout, is_repeat)){
        G_LOG_FC(LOG_ERROR, "timer start failed");
        return false;
    }
    m_timePassed = 0;
    m_repeated = 0;
    m_running = true;
    return true;
}

void TimerImp::stop(){
    uv_timer_stop(m_timer);
}
