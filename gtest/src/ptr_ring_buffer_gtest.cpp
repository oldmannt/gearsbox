//
//  ptr_ring_buffer_gtest.cpp
//  gearsbox
//
//  Created by dyno on 10/14/16.
//
//

#include <limits.h>
#include "gtest/gtest.h"
#include "ring_buffer_ptr.hpp"

#ifdef GEARSBOX_TEST
using namespace gearsbox;
// Step 2. Use the TEST macro to define your tests.
// Tests factorial of negative numbers.
TEST(ringbuffer, test) {
    
    uint32_t buffer_size = 10;
    std::shared_ptr<RingBufferPtr> buffer = RingBufferPtr::create(buffer_size);
    
    ASSERT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->getDistence(), buffer_size);
    EXPECT_EQ(buffer->getBufferSize(), buffer_size);
    uint32_t dis = buffer_size;
    
    uint32_t count = 8;
    for (uint32_t i=0; i<count; ++i) {
        buffer->push(std::make_shared<uint32_t>(i));
    }
    dis = buffer_size-count;
    EXPECT_EQ(buffer->getDistence(), dis);
    
    int32_t r_count = 8;
    for (uint32_t i=0; i<r_count; ++i) {
        std::shared_ptr<uint32_t> iptr = std::static_pointer_cast<uint32_t>(buffer->pop());
        ASSERT_NE(iptr, nullptr);
        EXPECT_EQ(*iptr, i);
    }
    // --------R&W-
    dis += r_count;
    EXPECT_EQ(buffer->getDistence(), dis);
    
    std::shared_ptr<uint32_t> read_ptr = std::static_pointer_cast<uint32_t>(buffer->pop());
    EXPECT_EQ(read_ptr, nullptr);
    EXPECT_EQ(buffer->getDistence(), dis);
    
    // -------W&R-
    count = dis;
    for (uint32_t i=0; i<count; ++i) {
        buffer->push(std::make_shared<uint32_t>(i));
    }
    dis -= count;
    EXPECT_EQ(buffer->getDistence(), dis);
    
    
    /*
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
    */
}
#endif
