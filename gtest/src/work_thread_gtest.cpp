//
//  work_thread_gtest.cpp
//  gearsbox
//
//  Created by dyno on 10/15/16.
//
//

#include <limits.h>
#include "gtest/gtest.h"
#include "work_thread.hpp"

#ifdef GEARSBOX_TEST
using namespace gearsbox;
// Step 2. Use the TEST macro to define your tests.
// Tests factorial of negative numbers.

void afterWork(){
    
}
/*
TEST(work_thread, test) {
    
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
    
    usleep(10000);
    ASSERT_EQ(finish, 1);
    ASSERT_EQ(worked, 1);
}
 */
#endif
