// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#include "video_frame_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol GBVideoFrameGen;

namespace djinni_generated {

class VideoFrameGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::VideoFrameGen>;
    using CppOptType = std::shared_ptr<::gearsbox::VideoFrameGen>;
    using ObjcType = id<GBVideoFrameGen>;

    using Boxed = VideoFrameGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
