// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace gearsbox {

class VideoEncoderGen;
class VideoFrameGen;

class VideoWriterGen {
public:
    virtual ~VideoWriterGen() {}

    static std::shared_ptr<VideoWriterGen> create();

    virtual void setFilePath(const std::string & file) = 0;

    virtual std::string getFilePath() = 0;

    virtual void setFPS(int32_t fps) = 0;

    virtual int32_t getFPS() = 0;

    virtual void setBitRate(int32_t rate) = 0;

    virtual void setVideoEncoder(const std::shared_ptr<VideoEncoderGen> & encoder) = 0;

    virtual void encodeFrame(const std::shared_ptr<VideoFrameGen> & frame) = 0;

    virtual void start(int64_t interval) = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual bool isRunning() = 0;

    virtual void setInterval(int64_t interval) = 0;

    virtual void saveNRlease() = 0;
};

}  // namespace gearsbox
