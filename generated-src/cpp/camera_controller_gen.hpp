// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include <cstdint>
#include <memory>

namespace gearsbox {

class VideoFrameGen;
enum class CameraFlash;
enum class CameraQuality;

class CameraControllerGen {
public:
    virtual ~CameraControllerGen() {}

    virtual void startCamera() = 0;

    virtual void stopCamera() = 0;

    virtual void setFlash(CameraFlash mode) = 0;

    virtual void setQuality(CameraQuality quality) = 0;

    virtual void switchFront(bool front) = 0;

    virtual bool isFront() = 0;

    virtual CameraFlash getFlash() = 0;

    virtual CameraQuality getQuality() = 0;

    virtual void setFousePoint(int32_t x, int32_t y) = 0;

    virtual void setExposurePoint(int32_t x, int32_t y) = 0;

    virtual void setZoom(float zoom) = 0;

    virtual float getZoom() = 0;

    virtual void setISO(int32_t iso) = 0;

    virtual int32_t getISO() = 0;

    virtual void setShutter(int32_t shutter) = 0;

    virtual int32_t getShutter() = 0;

    virtual void setAperture(float f) = 0;

    virtual float getAperture() = 0;

    virtual std::shared_ptr<VideoFrameGen> captureOneFrame() = 0;
};

}  // namespace gearsbox