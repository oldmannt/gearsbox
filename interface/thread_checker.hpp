//
//  thread_checker.h
//  gearsbox
//
//  Created by dyno on 10/27/16.
//
//

#ifndef thread_checker_h
#define thread_checker_h
#include <thread>

namespace gearsbox {
    
class ThreadChecker {
public:
    explicit ThreadChecker(){
        adopt();
    }
    virtual ~ThreadChecker(){
        
    }
    void adopt(){
        m_mother_thread = std::this_thread::get_id();
    }
    bool isMotherThread(){
        return std::this_thread::get_id()==m_mother_thread;
    }
private:
    std::thread::id m_mother_thread;
};
}


#endif /* thread_checker_h */
