// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import "GBCameraControllerGen+Private.h"
#import "GBCameraControllerGen.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"
#import "GBCameraCaptureHandler+Private.h"
#import "GBDuration+Private.h"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class CameraControllerGen::ObjcProxy final
: public ::gearsbox::CameraControllerGen
, public ::djinni::ObjcProxyCache::Handle<ObjcType>
{
public:
    using Handle::Handle;
    void initialize(bool c_audio) override
    {
        @autoreleasepool {
            [Handle::get() initialize:(::djinni::Bool::fromCpp(c_audio))];
        }
    }
    void setAudioEnable(bool c_enable) override
    {
        @autoreleasepool {
            [Handle::get() setAudioEnable:(::djinni::Bool::fromCpp(c_enable))];
        }
    }
    void startCamera() override
    {
        @autoreleasepool {
            [Handle::get() startCamera];
        }
    }
    void stopCamera() override
    {
        @autoreleasepool {
            [Handle::get() stopCamera];
        }
    }
    void switchFront(bool c_front) override
    {
        @autoreleasepool {
            [Handle::get() switchFront:(::djinni::Bool::fromCpp(c_front))];
        }
    }
    bool isFront() override
    {
        @autoreleasepool {
            auto r = [Handle::get() isFront];
            return ::djinni::Bool::toCpp(r);
        }
    }
    void setFlashMode(::gearsbox::CameraFlash c_mode) override
    {
        @autoreleasepool {
            [Handle::get() setFlashMode:(::djinni::Enum<::gearsbox::CameraFlash, GBCameraFlash>::fromCpp(c_mode))];
        }
    }
    ::gearsbox::CameraFlash getFlashMode() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFlashMode];
            return ::djinni::Enum<::gearsbox::CameraFlash, GBCameraFlash>::toCpp(r);
        }
    }
    void setQuality(::gearsbox::CameraQuality c_quality) override
    {
        @autoreleasepool {
            [Handle::get() setQuality:(::djinni::Enum<::gearsbox::CameraQuality, GBCameraQuality>::fromCpp(c_quality))];
        }
    }
    ::gearsbox::CameraQuality getQuality() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getQuality];
            return ::djinni::Enum<::gearsbox::CameraQuality, GBCameraQuality>::toCpp(r);
        }
    }
    void setSloMo(bool c_flag) override
    {
        @autoreleasepool {
            [Handle::get() setSloMo:(::djinni::Bool::fromCpp(c_flag))];
        }
    }
    bool getSloMo() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getSloMo];
            return ::djinni::Bool::toCpp(r);
        }
    }
    int32_t getMaxFrameRate() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getMaxFrameRate];
            return ::djinni::I32::toCpp(r);
        }
    }
    int32_t getDefaultFrameRate() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getDefaultFrameRate];
            return ::djinni::I32::toCpp(r);
        }
    }
    void setFrameDurationMin(const ::gearsbox::Duration & c_min) override
    {
        @autoreleasepool {
            [Handle::get() setFrameDurationMin:(::djinni_generated::Duration::fromCpp(c_min))];
        }
    }
    void setFrameDurationMax(const ::gearsbox::Duration & c_max) override
    {
        @autoreleasepool {
            [Handle::get() setFrameDurationMax:(::djinni_generated::Duration::fromCpp(c_max))];
        }
    }
    ::gearsbox::Duration getFrameDuration() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFrameDuration];
            return ::djinni_generated::Duration::toCpp(r);
        }
    }
    void setExposureMode(::gearsbox::CameraExposureMode c_mode) override
    {
        @autoreleasepool {
            [Handle::get() setExposureMode:(::djinni::Enum<::gearsbox::CameraExposureMode, GBCameraExposureMode>::fromCpp(c_mode))];
        }
    }
    ::gearsbox::CameraExposureMode getExposureMode() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureMode];
            return ::djinni::Enum<::gearsbox::CameraExposureMode, GBCameraExposureMode>::toCpp(r);
        }
    }
    void setExposurePoint(float c_x, float c_y) override
    {
        @autoreleasepool {
            [Handle::get() setExposurePoint:(::djinni::F32::fromCpp(c_x))
                                          y:(::djinni::F32::fromCpp(c_y))];
        }
    }
    void setExposureEv(float c_ev) override
    {
        @autoreleasepool {
            [Handle::get() setExposureEv:(::djinni::F32::fromCpp(c_ev))];
        }
    }
    float getExposureEv() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureEv];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getExposureMaxEv() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureMaxEv];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getExposureMinEv() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureMinEv];
            return ::djinni::F32::toCpp(r);
        }
    }
    void setExposureDuration(float c_seconds) override
    {
        @autoreleasepool {
            [Handle::get() setExposureDuration:(::djinni::F32::fromCpp(c_seconds))];
        }
    }
    float getExposureDuration() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureDuration];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getExposureMinDuration() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureMinDuration];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getExposureMaxDuration() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getExposureMaxDuration];
            return ::djinni::F32::toCpp(r);
        }
    }
    void setISO(int32_t c_iso) override
    {
        @autoreleasepool {
            [Handle::get() setISO:(::djinni::I32::fromCpp(c_iso))];
        }
    }
    int32_t getISO() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getISO];
            return ::djinni::I32::toCpp(r);
        }
    }
    int32_t getISOMax() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getISOMax];
            return ::djinni::I32::toCpp(r);
        }
    }
    int32_t getISOMin() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getISOMin];
            return ::djinni::I32::toCpp(r);
        }
    }
    float getEV() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getEV];
            return ::djinni::F32::toCpp(r);
        }
    }
    void setEV(float c_ev) override
    {
        @autoreleasepool {
            [Handle::get() setEV:(::djinni::F32::fromCpp(c_ev))];
        }
    }
    float getEVMax() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getEVMax];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getEVMin() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getEVMin];
            return ::djinni::F32::toCpp(r);
        }
    }
    void setFocusMode(::gearsbox::CameraFocusMode c_mode) override
    {
        @autoreleasepool {
            [Handle::get() setFocusMode:(::djinni::Enum<::gearsbox::CameraFocusMode, GBCameraFocusMode>::fromCpp(c_mode))];
        }
    }
    ::gearsbox::CameraFocusMode getFocusMode() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFocusMode];
            return ::djinni::Enum<::gearsbox::CameraFocusMode, GBCameraFocusMode>::toCpp(r);
        }
    }
    void setFocusLens(float c_lens) override
    {
        @autoreleasepool {
            [Handle::get() setFocusLens:(::djinni::F32::fromCpp(c_lens))];
        }
    }
    float getFocusLens() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFocusLens];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getFocusMax() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFocusMax];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getFocusMin() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFocusMin];
            return ::djinni::F32::toCpp(r);
        }
    }
    void setFocusPoint(float c_x, float c_y) override
    {
        @autoreleasepool {
            [Handle::get() setFocusPoint:(::djinni::F32::fromCpp(c_x))
                                       y:(::djinni::F32::fromCpp(c_y))];
        }
    }
    void setFocusAutoRange(::gearsbox::CameraFocusRange c_range) override
    {
        @autoreleasepool {
            [Handle::get() setFocusAutoRange:(::djinni::Enum<::gearsbox::CameraFocusRange, GBCameraFocusRange>::fromCpp(c_range))];
        }
    }
    ::gearsbox::CameraFocusRange getFocusAutoRange() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFocusAutoRange];
            return ::djinni::Enum<::gearsbox::CameraFocusRange, GBCameraFocusRange>::toCpp(r);
        }
    }
    void setZoom(float c_zoom) override
    {
        @autoreleasepool {
            [Handle::get() setZoom:(::djinni::F32::fromCpp(c_zoom))];
        }
    }
    float getZoom() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getZoom];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getZoomMax() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getZoomMax];
            return ::djinni::F32::toCpp(r);
        }
    }
    float getZoomMin() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getZoomMin];
            return ::djinni::F32::toCpp(r);
        }
    }
    void asnyOneFrame() override
    {
        @autoreleasepool {
            [Handle::get() asnyOneFrame];
        }
    }
    void asnyOnePicture() override
    {
        @autoreleasepool {
            [Handle::get() asnyOnePicture];
        }
    }
    void setCaptureHandler(const std::shared_ptr<::gearsbox::CameraCaptureHandler> & c_handler) override
    {
        @autoreleasepool {
            [Handle::get() setCaptureHandler:(::djinni_generated::CameraCaptureHandler::fromCpp(c_handler))];
        }
    }
    void setCaptureMode(::gearsbox::CameraCaptureMode c_mode) override
    {
        @autoreleasepool {
            [Handle::get() setCaptureMode:(::djinni::Enum<::gearsbox::CameraCaptureMode, GBCameraCaptureMode>::fromCpp(c_mode))];
        }
    }
    ::gearsbox::CameraCaptureMode getCaptureMode() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getCaptureMode];
            return ::djinni::Enum<::gearsbox::CameraCaptureMode, GBCameraCaptureMode>::toCpp(r);
        }
    }
    void setImmediaPause(bool c_flag) override
    {
        @autoreleasepool {
            [Handle::get() setImmediaPause:(::djinni::Bool::fromCpp(c_flag))];
        }
    }
    std::string getDebugInfo() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getDebugInfo];
            return ::djinni::String::toCpp(r);
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto CameraControllerGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto CameraControllerGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return dynamic_cast<ObjcProxy&>(*cpp).Handle::get();
}

}  // namespace djinni_generated
