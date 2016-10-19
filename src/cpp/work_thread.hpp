//
//  work_thread.hpp
//  gearsbox
//
//  Created by dyno on 10/15/16.
//
//

#ifndef work_thread_hpp
#define work_thread_hpp

#include "uv.h"
#include <functional>

namespace gearsbox {

class WorkThread {
public:
    WorkThread(std::function<void()> funnc,
               std::function<void()> after_work)
    :m_fn(std::move(funnc)), m_rt(std::move(after_work)),m_running(false) {
    }
    
    ~WorkThread(){
        m_fn = nullptr;
        m_rt = nullptr;
    }
    void start();
    bool isRuning(){return m_running;}
    void work();
    void afterWork();
    // only work when the thread is not yet to start
    void cancel();
private:
    uv_work_t m_work;
    std::function<void()> m_fn;
    std::function<void()> m_rt;
    bool m_running;
};

}
#endif /* work_thread_hpp */
