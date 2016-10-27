// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include <cstdint>
#include <utility>

namespace gearsbox {

struct Duration final {
    int64_t value;
    int32_t scale;

    Duration(int64_t value_,
             int32_t scale_)
    : value(std::move(value_))
    , scale(std::move(scale_))
    {}
};

}  // namespace gearsbox