//
//  test_event.cpp
//  gearsbox
//
//  Created by dyno on 6/19/16.
//
//
#include <stdio.h>
#include "ilog.h"
#include "uv.h"

#include "work_thread.hpp"

using namespace gearsbox;

class test{
public:
    int32_t flag;
};
int main(int argc, char **argv) {
    
    int32_t finish = 0;
    int32_t worked = 0;
    
    std::function<void()> after_work = [&finish](){
        finish = 1;
    };
    
    std::function<void()> work = [&worked](){
        worked = 1;
    };
    
    WorkThread work_thread(work, after_work);
    work_thread.start();
    
    return uv_run(uv_default_loop(),UV_RUN_DEFAULT);
}

