// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#include "camera_config_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class GBCameraConfigGen;

namespace djinni_generated {

class CameraConfigGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::CameraConfigGen>;
    using CppOptType = std::shared_ptr<::gearsbox::CameraConfigGen>;
    using ObjcType = GBCameraConfigGen*;

    using Boxed = CameraConfigGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
