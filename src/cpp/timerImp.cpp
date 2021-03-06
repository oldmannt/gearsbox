//
//  TimerImp.cpp
//  gearsbox
//
//  Created by dyno on 6/8/16.
//
//

#include "TimerImp.hpp"
#include "task_manager_gen.hpp"
#include "macro.h"
#include <unordered_map>

using namespace gearsbox;

std::shared_ptr<TimerGen> TimerGen::create(int64_t interval, int32_t repeat_times, const std::shared_ptr<TaskExcuserGen> & hander){
    CHECK_RTP(interval>0, nullptr, "interval invaild value:%d", interval);
    return std::make_shared<TimerImp>(interval, repeat_times, hander);
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

TimerImp::TimerImp(int64_t interval, int32_t repeat, std::shared_ptr<TaskExcuserGen> handler)
:m_interval(interval),
m_timePassed(0),
m_repeatTimes(repeat),
m_repeated(0),
m_running(false),
m_handler(handler){
    m_timer = new uv_timer_t();
    m_timer->data = this;
    uv_timer_init(uv_default_loop(), m_timer);
    m_handleinfo = TaskManagerGen::create_info(0, interval, repeat);
}

TimerImp::~TimerImp() {
    uv_timer_stop(m_timer);
    uv_close((uv_handle_t*)m_timer, close_timer_cb);
    m_handler = nullptr;
}

void TimerImp::timerCallback(){
    m_timePassed += m_interval;
    if (!m_running)
        return;
    ++m_repeated;
    
    m_handleinfo->setDelay(m_interval);
    m_handleinfo->setRepeated(m_repeated);
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
    //G_LOG_FC(LOG_ERROR, "timer start interval:%d, is_repeat:%d", m_interval, is_repeat);
    if (0 != uv_timer_start(m_timer, timer_cb, m_interval, is_repeat)){
        G_LOG_FC(LOG_ERROR, "timer start failed");
        return false;
    }
    m_timePassed = 0;
    m_repeated = 0;
    m_running = true;
    m_handleinfo->setAssignTick(uv_now(uv_default_loop()));
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
