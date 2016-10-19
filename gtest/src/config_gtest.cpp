//
//  config_gtest.cpp
//  gearsbox
//
//  Created by dyno on 6/18/16.
//
//

#include <limits.h>
#include "gtest/gtest.h"
#include "config_gen.hpp"
#include "lang_type.hpp"
#include <cmath>

#ifdef GEARSBOX_TEST
using namespace gearsbox;
// Step 2. Use the TEST macro to define your tests.
// Tests factorial of negative numbers.
TEST(config, read) {
    return;
    const std::string path = "/Users/dyno/Documents/develop/usnit/data/user.json";
    std::shared_ptr<ConfigGen> config = ConfigGen::create();
    
    ASSERT_NE(config, nullptr);
    
    EXPECT_EQ(config->initialize(path), true);
    
    EXPECT_EQ(config->getString("language"), "ch");
    EXPECT_LT(std::abs(config->getFloat("exchange_ask")-6.5718f), 0.0001f);
    EXPECT_LT(std::abs(config->getFloat("exchange_bid")-6.5705f), 0.0001f);
    EXPECT_LT(std::abs(config->getFloat("exchange_rate")-6.5705f), 0.0001f);
    EXPECT_EQ(config->getInt("start_counter"), 1);
    EXPECT_EQ(config->getString("exchange_date"), "5/18/2016");
    EXPECT_EQ(config->getString("mass"), "gram");
    EXPECT_EQ(config->getString("volume"), "liter");
    EXPECT_EQ(config->getString("square"), "sqmeter");
    EXPECT_EQ(config->getString("termperature"), "celcius");
    EXPECT_EQ(config->getString("exchange"), "rmb");
    EXPECT_EQ(config->getString("exchange_url"), "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20yahoo.finance.xchange%20where%20pair%20in%20(%22USDCNY%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
    
}
#endif
