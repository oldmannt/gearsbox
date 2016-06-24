// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <utility>

namespace gearsbox {

struct ArgbColor final {

    static ArgbColor const NOCOLOR;

    static ArgbColor const REDCOLOR;

    static ArgbColor const GREENCOLOR;

    static ArgbColor const BLUECOLOR;

    static ArgbColor const BLACKCOLOR;

    static ArgbColor const WHITECOLOR;
    float a;
    float r;
    float g;
    float b;

    ArgbColor(float a_,
              float r_,
              float g_,
              float b_)
    : a(std::move(a_))
    , r(std::move(r_))
    , g(std::move(g_))
    , b(std::move(b_))
    {}
};

}  // namespace gearsbox
