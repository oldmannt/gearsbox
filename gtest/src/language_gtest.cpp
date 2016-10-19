// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "gtest/gtest.h"
#include "language_store_gen.hpp"
#include "lang_type.hpp"

#ifdef GEARSBOX_TEST
using namespace gearsbox;
// Step 2. Use the TEST macro to define your tests.
// Tests factorial of negative numbers.
TEST(language, readtest) {
    return;
    const std::string path = "/Users/dyno/Documents/develop/usnit/data/language.json";
    std::shared_ptr<LanguageStoreGen> lang = LanguageStoreGen::instance();
    
    ASSERT_NE(lang, nullptr);
    
    EXPECT_EQ(lang->initialize(path), true);
    lang->setLanguage(LangType::LANG_CHS);
    EXPECT_EQ(lang->getLanguage(), LangType::LANG_CHS);
    
    EXPECT_EQ(lang->getString("time_zone_bj"), "北京时间:");
    EXPECT_EQ(lang->getString("time_zone_usw"), "美国西部时间:");
    EXPECT_EQ(lang->getString("time_zone_usm"), "美国中部时间:");
    EXPECT_EQ(lang->getString("time_zone_use"), "美国东部时间:");
    
    EXPECT_EQ(lang->getString("time_format"), " %m月%d日 %R");
    EXPECT_EQ(lang->getString("exchange_info"), "%s的离岸汇率,汇卖价:%.04f,汇买价:%.04f");
    EXPECT_EQ(lang->getString("meter"), "米");
    EXPECT_EQ(lang->getString("cmeter"), "厘米");
    EXPECT_EQ(lang->getString("kmeter"), "公里");
    EXPECT_EQ(lang->getString("feet"), "英尺");
    EXPECT_EQ(lang->getString("inch"), "英寸");
    EXPECT_EQ(lang->getString("mile"), "英里");
    EXPECT_EQ(lang->getString("yard"), "码");
    EXPECT_EQ(lang->getString("gram"), "克");
    EXPECT_EQ(lang->getString("kgram"), "千克");
    EXPECT_EQ(lang->getString("lb"), "磅");
    EXPECT_EQ(lang->getString("oz"), "盎司");
    EXPECT_EQ(lang->getString("mliter"), "毫升");
    EXPECT_EQ(lang->getString("gal"), "加仑");
    EXPECT_EQ(lang->getString("sqmeter"), "平方米");
    EXPECT_EQ(lang->getString("sqcmeter"), "平方厘米");
    EXPECT_EQ(lang->getString("sqinch"), "平方英寸");
    EXPECT_EQ(lang->getString("sqfeet"), "平方英尺");
    EXPECT_EQ(lang->getString("celcius"), "摄氏度");
    EXPECT_EQ(lang->getString("fahrenheit"), "华氏度");
    EXPECT_EQ(lang->getString("rmb"), "元");
    EXPECT_EQ(lang->getString("dollor"), "美元");
    
    lang->setLanguage(LangType::LANG_ENG);
    EXPECT_EQ(lang->getLanguage(), LangType::LANG_ENG);
    
    EXPECT_EQ(lang->getString("time_zone_bj"), "Beijing:");
    EXPECT_EQ(lang->getString("time_zone_usw"), "west us:");
    EXPECT_EQ(lang->getString("time_zone_usm"), "middle us:");
    EXPECT_EQ(lang->getString("time_zone_use"), "east us:");
    
    EXPECT_EQ(lang->getString("time_format"), " %b %d %R");
    EXPECT_EQ(lang->getString("exchange_info"), "From Yahoo:%s Buying Rate:%.04f Selling Rate:%.04f");
    EXPECT_EQ(lang->getString("meter"), "m");
    EXPECT_EQ(lang->getString("cmeter"), "cm");
    EXPECT_EQ(lang->getString("kmeter"), "km");
    EXPECT_EQ(lang->getString("feet"), "ft");
    EXPECT_EQ(lang->getString("inch"), "inch");
    EXPECT_EQ(lang->getString("mile"), "mile");
    EXPECT_EQ(lang->getString("yard"), "yard");
    EXPECT_EQ(lang->getString("gram"), "gram");
    EXPECT_EQ(lang->getString("kgram"), "kg");
    EXPECT_EQ(lang->getString("lb"), "lb");
    EXPECT_EQ(lang->getString("oz"), "oz");
    EXPECT_EQ(lang->getString("mliter"), "ml");
    EXPECT_EQ(lang->getString("gal"), "gal");
    EXPECT_EQ(lang->getString("sqmeter"), "m²");
    EXPECT_EQ(lang->getString("sqcmeter"), "cm²");
    EXPECT_EQ(lang->getString("sqinch"), "inch²");
    EXPECT_EQ(lang->getString("sqfeet"), "ft²");
    EXPECT_EQ(lang->getString("celcius"), "°C");
    EXPECT_EQ(lang->getString("fahrenheit"), "°F");
    EXPECT_EQ(lang->getString("rmb"), "¥");
    EXPECT_EQ(lang->getString("dollor"), "$");
    
}


// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
#endif
