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

    virtual int32_t getLineSize() = 0;

    virtual void setData(int64_t data) = 0;

    virtual void setWidth(int32_t width) = 0;

    virtual void setHeight(int32_t height) = 0;

    virtual void setSize(int64_t size) = 0;

    virtual void setLineSize(int32_t linesize) = 0;
};

}  // namespace gearsbox
