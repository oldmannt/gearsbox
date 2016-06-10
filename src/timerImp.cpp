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

std::shared_ptr<TimerGen> TimerGen::create(int64_t timeout, int32_t repeat_times, const std::shared_ptr<TimerHandlerGen> & hander){
    return std::make_shared<TimerImp>(timeout, repeat_times, hander);
}

TimerImp::TimerImp(int64_t timeout, int32_t repeat, std::shared_ptr<TimerHandlerGen> handler)
:m_timeout(timeout),
m_timePassed(0),
m_repeatTimes(repeat),
m_repeated(0),
m_running(false),
m_handler(handler){
    m_timer.data = this;
    uv_timer_init(uv_default_loop(), &m_timer);
}

TimerImp::~TimerImp() {
    uv_close((uv_handle_t*)&m_timer, 0);
}

typedef std::unordered_map<uv_timer_t*, TimerImp*> MapTimer;
static MapTimer s_timerMap;
static void timer_cb(uv_timer_t* handle) {
    if (!handle || handle->data){
        return;
    }
    
    TimerImp* timerimp = (TimerImp*)handle->data;
    timerimp->timerCallback();
}

void TimerImp::timerCallback(){
    m_timePassed += m_timeout;
    ++m_repeated;
    
    if (m_handler)
        m_handler->handler(m_timePassed, m_repeated);
    
    if (m_repeated<m_repeatTimes){
        return;
    }
    
    uv_timer_stop(&m_timer);
    m_running = false;
}

bool TimerImp::start(){
    uint64_t is_repeat = m_repeated==0?0:1;
    if (0 != uv_timer_start(&m_timer, timer_cb, m_timeout, is_repeat)){
        G_LOG_FC(LOG_ERROR, "timer start failed");
        return false;
    }
    m_timePassed = 0;
    m_repeated = 0;
    m_running = true;
    return true;
}

void TimerImp::stop(){
    uv_timer_stop(&m_timer);
}
