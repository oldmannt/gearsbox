// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include <cstdint>
#include <memory>

namespace gearsbox {

class CameraCaptureHandler;
class VideoFrameGen;
enum class CameraExposureMode;
enum class CameraFlash;
enum class CameraFocusMode;
enum class CameraFocusRange;
enum class CameraQuality;

class CameraControllerGen {
public:
    virtual ~CameraControllerGen() {}

    virtual void startCamera() = 0;

    virtual void stopCamera() = 0;

    virtual void switchFront(bool front) = 0;

    virtual bool isFront() = 0;

    virtual void setFlashMode(CameraFlash mode) = 0;

    virtual CameraFlash getFlashMode() = 0;

    virtual void setQuality(CameraQuality quality) = 0;

    virtual CameraQuality getQuality() = 0;

    virtual void setExposureMode(CameraExposureMode mode) = 0;

    virtual CameraExposureMode getExposureMode() = 0;

    virtual void setExposurePoint(float x, float y) = 0;

    virtual void setExposureEv(float ev) = 0;

    virtual float getExposureEv() = 0;

    virtual float getExposureMaxEv() = 0;

    virtual float getExposureMinEv() = 0;

    virtual void setExposureDuration(float seconds) = 0;

    virtual float getExposureDuration() = 0;

    virtual float getExposureMinDuration() = 0;

    virtual float getExposureMaxDuration() = 0;

    virtual void setISO(int32_t iso) = 0;

    virtual int32_t getISO() = 0;

    virtual int32_t getISOMax() = 0;

    virtual int32_t getISOMin() = 0;

    virtual void setFocusMode(CameraFocusMode mode) = 0;

    virtual CameraFocusMode getFocusMode() = 0;

    /** lens form 0.0 to 1.0, shortest to furthest */
    virtual void setFocusLens(float lens) = 0;

    virtual float getFocusLens() = 0;

    virtual float getFocusMax() = 0;

    virtual float getFocusMin() = 0;

    virtual void setFocusPoint(float x, float y) = 0;

    virtual void setFocusAutoRange(CameraFocusRange range) = 0;

    virtual CameraFocusRange getFocusAutoRange() = 0;

    virtual void setZoom(float zoom) = 0;

    virtual float getZoom() = 0;

    virtual float getZoomMax() = 0;

    /** minimum value is 1.0 */
    virtual float getZoomMin() = 0;

    virtual void setFramePhoto(bool flag) = 0;

    virtual std::shared_ptr<VideoFrameGen> captureOneFrame() = 0;

    virtual void asnyOneFrame() = 0;

    virtual void asnyOnePicture() = 0;

    virtual void setCaptureHandler(const std::shared_ptr<CameraCaptureHandler> & handler) = 0;
};

}  // namespace gearsbox
