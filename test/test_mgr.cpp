//
//  test_event.cpp
//  gearsbox
//
//  Created by dyno on 6/19/16.
//
//
#include <stdio.h>

#include "gtest/gtest.h"
#include "ilog.h"

#include "test_mgr.hpp"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

using namespace gearsbox;
    
    // Provides alternative output mode which produces minimal amount of
    // information about tests.
    class TersePrinter : public EmptyTestEventListener {
    private:
        // Called before any test activity starts.
        virtual void OnTestProgramStart(const UnitTest& /* unit_test */) {}
        
        // Called after all test activities have ended.
        virtual void OnTestProgramEnd(const UnitTest& unit_test) {
            G_LOG_LX("TEST %s", unit_test.Passed() ? "PASSED" : "FAILED");
            //fprintf(stdout, "TEST %s\n", unit_test.Passed() ? "PASSED" : "FAILED");
            //fflush(stdout);
        }
        
        // Called before a test starts.
        virtual void OnTestStart(const TestInfo& test_info) {
            G_LOG_LX("*** Test %s.%s starting.",
                     test_info.test_case_name(),
                     test_info.name());
            //fprintf(stdout,
            //        "*** Test %s.%s starting.\n",
            //        test_info.test_case_name(),
            //        test_info.name());
            //fflush(stdout);
        }
        
        // Called after a failed assertion or a SUCCEED() invocation.
        virtual void OnTestPartResult(const TestPartResult& test_part_result) {
            G_LOG_LX("%s in %s:%d\n%s",
                    test_part_result.failed() ? "*** Failure" : "Success",
                    test_part_result.file_name(),
                    test_part_result.line_number(),
                    test_part_result.summary());
            //fprintf(stdout,
            //        "%s in %s:%d\n%s\n",
            //        test_part_result.failed() ? "*** Failure" : "Success",
            //        test_part_result.file_name(),
            //        test_part_result.line_number(),
            //        test_part_result.summary());
            //fflush(stdout);
        }
        
        // Called after a test ends.
        virtual void OnTestEnd(const TestInfo& test_info) {
            G_LOG_LX("*** Test %s.%s ending.",
                    test_info.test_case_name(),
                    test_info.name());
            //fprintf(stdout,
            //        "*** Test %s.%s ending.\n",
            //        test_info.test_case_name(),
            //        test_info.name());
            //fflush(stdout);
        }
    };  // class TersePrinter


std::shared_ptr<TestMgrGen> TestMgrGen::instance(){
    static std::shared_ptr<TestMgrGen> s_ptr = std::make_shared<TestMgrImp>();
    return s_ptr;
}

bool TestMgrImp::initialize(const std::string & self_path){
    int argc = 1;
    char path[512] = {0};
    char terse[64] = {"--terse_output"};
    char *param[2] = {path,terse};
    strncpy(path, self_path.c_str(), sizeof(path));
    InitGoogleTest(&argc, param);
    
    //UnitTest& unit_test = *UnitTest::GetInstance();
    //TestEventListeners& listeners = unit_test.listeners();
    //delete listeners.Release(listeners.default_result_printer());
    //listeners.Append(new TersePrinter);
    
    return true;
}

int32_t TestMgrImp::runTests(){
    int ret_val = RUN_ALL_TESTS();
    
    UnitTest& unit_test = *UnitTest::GetInstance();
    // This is an example of using the UnitTest reflection API to inspect test
    // results. Here we discount failures from the tests we expected to fail.
    int unexpectedly_failed_tests = 0;
    for (int i = 0; i < unit_test.total_test_case_count(); ++i) {
        const TestCase& test_case = *unit_test.GetTestCase(i);
        for (int j = 0; j < test_case.total_test_count(); ++j) {
            const TestInfo& test_info = *test_case.GetTestInfo(j);
            // Counts failed tests that were not meant to fail (those without
            // 'Fails' in the name).
            if (test_info.result()->Failed() &&
                strcmp(test_info.name(), "Fails") != 0) {
                unexpectedly_failed_tests++;
            }
        }
    }
    
    // Test that were meant to fail should not affect the test program outcome.
    if (unexpectedly_failed_tests == 0)
        ret_val = 0;
    
    return ret_val;
}

#ifdef TEST_STAND_ALONE
int main(int argc, char **argv) {
    TestMgrGen::instance()->initialize(argv[0]);
    TestMgrGen::instance()->runTests();
    
}
#endif
