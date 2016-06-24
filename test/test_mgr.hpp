//
//  test_event.hpp
//  gearsbox
//
//  Created by dyno on 6/19/16.
//
//

#ifndef test_mgr_h
#define test_mgr_h

#include "test_mgr_gen.hpp"

namespace gearsbox {
    
class TestMgrImp: public TestMgrGen {
public:
    virtual ~TestMgrImp() {}
    
    virtual bool initialize(const std::string & self_path);
    
    virtual int32_t runTests();
};
}

#endif /* test_event_h */
