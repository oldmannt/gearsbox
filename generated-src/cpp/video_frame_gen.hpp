// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include <cstdint>

namespace gearsbox {

class VideoFrameGen {
public:
    virtual ~VideoFrameGen() {}

    virtual int64_t getData() = 0;

    virtual int32_t getWidth() = 0;

    virtual int32_t getHeight() = 0;

    virtual int64_t getSize() = 0;
};

}  // namespace gearsbox
