// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#include "camera_capture_handler.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol GBCameraCaptureHandler;

namespace djinni_generated {

class CameraCaptureHandler
{
public:
    using CppType = std::shared_ptr<::gearsbox::CameraCaptureHandler>;
    using CppOptType = std::shared_ptr<::gearsbox::CameraCaptureHandler>;
    using ObjcType = id<GBCameraCaptureHandler>;

    using Boxed = CameraCaptureHandler;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
