// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include <cstdint>
#include <utility>

namespace gearsbox {

struct TaskInfo final {
    int64_t delay;
    bool repeate;

    TaskInfo(int64_t delay_,
             bool repeate_)
    : delay(std::move(delay_))
    , repeate(std::move(repeate_))
    {}
};

}  // namespace gearsbox
