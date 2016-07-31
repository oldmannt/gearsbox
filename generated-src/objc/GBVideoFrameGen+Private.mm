// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import "GBVideoFrameGen+Private.h"
#import "GBVideoFrameGen.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class VideoFrameGen::ObjcProxy final
: public ::gearsbox::VideoFrameGen
, public ::djinni::ObjcProxyCache::Handle<ObjcType>
{
public:
    using Handle::Handle;
    int64_t getData() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getData];
            return ::djinni::I64::toCpp(r);
        }
    }
    int32_t getWidth() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getWidth];
            return ::djinni::I32::toCpp(r);
        }
    }
    int32_t getHeight() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getHeight];
            return ::djinni::I32::toCpp(r);
        }
    }
    int64_t getSize() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getSize];
            return ::djinni::I64::toCpp(r);
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto VideoFrameGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto VideoFrameGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return dynamic_cast<ObjcProxy&>(*cpp).Handle::get();
}

}  // namespace djinni_generated