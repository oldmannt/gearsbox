// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import "GBCameraControllerGen+Private.h"
#import "GBCameraControllerGen.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"
#import "GBVideoFrameGen+Private.h"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class CameraControllerGen::ObjcProxy final
: public ::gearsbox::CameraControllerGen
, public ::djinni::ObjcProxyCache::Handle<ObjcType>
{
public:
    using Handle::Handle;
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
    void setFlash(::gearsbox::CameraFlash c_mode) override
    {
        @autoreleasepool {
            [Handle::get() setFlash:(::djinni::Enum<::gearsbox::CameraFlash, GBCameraFlash>::fromCpp(c_mode))];
        }
    }
    void setQuality(::gearsbox::CameraQuality c_quality) override
    {
        @autoreleasepool {
            [Handle::get() setQuality:(::djinni::Enum<::gearsbox::CameraQuality, GBCameraQuality>::fromCpp(c_quality))];
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
    ::gearsbox::CameraFlash getFlash() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getFlash];
            return ::djinni::Enum<::gearsbox::CameraFlash, GBCameraFlash>::toCpp(r);
        }
    }
    ::gearsbox::CameraQuality getQuality() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getQuality];
            return ::djinni::Enum<::gearsbox::CameraQuality, GBCameraQuality>::toCpp(r);
        }
    }
    void setFousePoint(int32_t c_x, int32_t c_y) override
    {
        @autoreleasepool {
            [Handle::get() setFousePoint:(::djinni::I32::fromCpp(c_x))
                                       y:(::djinni::I32::fromCpp(c_y))];
        }
    }
    void setExposurePoint(int32_t c_x, int32_t c_y) override
    {
        @autoreleasepool {
            [Handle::get() setExposurePoint:(::djinni::I32::fromCpp(c_x))
                                          y:(::djinni::I32::fromCpp(c_y))];
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
    void setShutter(int32_t c_shutter) override
    {
        @autoreleasepool {
            [Handle::get() setShutter:(::djinni::I32::fromCpp(c_shutter))];
        }
    }
    int32_t getShutter() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getShutter];
            return ::djinni::I32::toCpp(r);
        }
    }
    void setAperture(float c_f) override
    {
        @autoreleasepool {
            [Handle::get() setAperture:(::djinni::F32::fromCpp(c_f))];
        }
    }
    float getAperture() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getAperture];
            return ::djinni::F32::toCpp(r);
        }
    }
    std::shared_ptr<::gearsbox::VideoFrameGen> captureOneFrame() override
    {
        @autoreleasepool {
            auto r = [Handle::get() captureOneFrame];
            return ::djinni_generated::VideoFrameGen::toCpp(r);
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
