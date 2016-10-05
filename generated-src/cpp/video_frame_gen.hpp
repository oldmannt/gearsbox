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

    virtual int64_t getAudioData() = 0;

    virtual int64_t getAudioDataSize() = 0;

    virtual int64_t getAudioPSTValue() = 0;

    virtual int32_t getAudioPSTScale() = 0;

    virtual int32_t getNumSamples() = 0;

    virtual int32_t getChannelsPerFrame() = 0;

    virtual double getSampleRate() = 0;

    virtual int32_t getBitsPerChannel() = 0;

    virtual void setAudioData(int64_t data) = 0;

    virtual void setAudioDataSize(int64_t size) = 0;

    virtual void setAudioPSTValue(int64_t value) = 0;

    virtual void setAudioPSTScale(int32_t scale) = 0;

    virtual void setNumSamples(int32_t num) = 0;

    virtual void setChannelsPerFrame(int32_t channels) = 0;

    virtual void setSampleRate(double rate) = 0;

    virtual void setBitsPerChannel(int32_t bits) = 0;
};

}  // namespace gearsbox
