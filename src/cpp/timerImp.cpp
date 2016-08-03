//
//  TimerImp.cpp
//  gearsbox
//
//  Created by dyno on 6/8/16.
//
//

#include "TimerImp.hpp"
#include "ILog.h"
#include <unordered_map>

using namespace gearsbox;

std::shared_ptr<TimerGen> TimerGen::create(int64_t task_id, int64_t interval, int32_t repeat_times, const std::shared_ptr<TaskExcuserGen> & hander){
    return std::make_shared<TimerImp>(task_id, interval, repeat_times, hander);
}

int64_t TimerGen::currentTick(){
    return uv_now(uv_default_loop());
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

TimerImp::TimerImp(int64_t task_id, int64_t interval, int32_t repeat, std::shared_ptr<TaskExcuserGen> handler)
:m_interval(interval),
m_timePassed(0),
m_repeatTimes(repeat),
m_repeated(0),
m_running(false),
m_handler(handler),
m_handleinfo(task_id, interval, repeat, repeat){
    m_timer = new uv_timer_t();
    m_timer->data = this;
    uv_timer_init(uv_default_loop(), m_timer);
}

TimerImp::~TimerImp() {
    uv_close((uv_handle_t*)m_timer, close_timer_cb);
    m_handler = nullptr;
}

void TimerImp::timerCallback(){
    m_timePassed += m_interval;
    if (!m_running)
        return;
    ++m_repeated;
    
    m_handleinfo.delay = m_interval;
    m_handleinfo.elapsed = m_timePassed;
    m_handleinfo.repeated = m_repeated;
    if (m_handler)
        m_handler->excuse(m_handleinfo);
    
    if (m_repeatTimes<0 || m_repeated<m_repeatTimes){
        return;
    }
    
    uv_timer_stop(m_timer);
    m_running = false;
}

bool TimerImp::start(){
    uint64_t is_repeat = m_repeatTimes==0?0:m_interval;
    if (0 != uv_timer_start(m_timer, timer_cb, m_interval, is_repeat)){
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

void TimerImp::pause(){
    m_running = false;
}

void TimerImp::resume(){
    m_running = true;
}

void TimerImp::setInterval(int64_t interval){
    m_interval = interval;
    uv_timer_set_repeat(m_timer, interval);
}

int64_t TimerImp::getInterval(){
    return m_interval;
}
