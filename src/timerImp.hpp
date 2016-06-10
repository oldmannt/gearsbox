//
//  TimerImp.hpp
//  gearsbox
//
//  Created by dyno on 6/8/16.
//
//

#ifndef TimerImp_hpp
#define TimerImp_hpp

#include "timer_gen.hpp"
#include "timer_handler_gen.hpp"
#include "uv.h"

namespace gearsbox {

class TimerImp:public TimerGen {
public:
    virtual bool start();
    virtual void stop();
    virtual int32_t getRepeated(){return m_repeated;}
    virtual int64_t getTimePassed(){return m_timePassed;}
    virtual bool isRunning(){return m_running;}
    
    TimerImp(int64_t timeout, int32_t repeat, std::shared_ptr<TimerHandlerGen> handler);
    virtual ~TimerImp();
    void timerCallback();
    
private:
    int64_t m_timeout;
    int64_t m_timePassed;
    int32_t m_repeatTimes;
    int32_t m_repeated;
    bool m_running;
    std::shared_ptr<TimerHandlerGen> m_handler;
    uv_timer_t m_timer;
};
    
}


#endif /* TimerImp_hpp */
