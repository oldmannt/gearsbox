// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import "GBVideoEncoderGen+Private.h"
#import "GBVideoEncoderGen.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"
#import "GBVideoFrameGen+Private.h"
#include <exception>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface GBVideoEncoderGenCppProxy : NSObject<GBVideoEncoderGen>

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::VideoEncoderGen>&)cppRef;

@end

@implementation GBVideoEncoderGenCppProxy {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::gearsbox::VideoEncoderGen>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::VideoEncoderGen>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

- (BOOL)initialize:(nonnull NSString *)filepath
               fps:(int32_t)fps
           bitrate:(int32_t)bitrate
             width:(int32_t)width
            height:(int32_t)height {
    try {
        auto r = _cppRefHandle.get()->initialize(::djinni::String::toCpp(filepath),
                                                 ::djinni::I32::toCpp(fps),
                                                 ::djinni::I32::toCpp(bitrate),
                                                 ::djinni::I32::toCpp(width),
                                                 ::djinni::I32::toCpp(height));
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)encodeFrame:(nullable id<GBVideoFrameGen>)frame {
    try {
        _cppRefHandle.get()->encodeFrame(::djinni_generated::VideoFrameGen::toCpp(frame));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)saveNRelease {
    try {
        _cppRefHandle.get()->saveNRelease();
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace djinni_generated {

class VideoEncoderGen::ObjcProxy final
: public ::gearsbox::VideoEncoderGen
, public ::djinni::ObjcProxyCache::Handle<ObjcType>
{
public:
    using Handle::Handle;
    bool initialize(const std::string & c_filepath, int32_t c_fps, int32_t c_bitrate, int32_t c_width, int32_t c_height) override
    {
        @autoreleasepool {
            auto r = [Handle::get() initialize:(::djinni::String::fromCpp(c_filepath))
                                           fps:(::djinni::I32::fromCpp(c_fps))
                                       bitrate:(::djinni::I32::fromCpp(c_bitrate))
                                         width:(::djinni::I32::fromCpp(c_width))
                                        height:(::djinni::I32::fromCpp(c_height))];
            return ::djinni::Bool::toCpp(r);
        }
    }
    void encodeFrame(const std::shared_ptr<::gearsbox::VideoFrameGen> & c_frame) override
    {
        @autoreleasepool {
            [Handle::get() encodeFrame:(::djinni_generated::VideoFrameGen::fromCpp(c_frame))];
        }
    }
    void saveNRelease() override
    {
        @autoreleasepool {
            [Handle::get() saveNRelease];
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto VideoEncoderGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    if ([(id)objc isKindOfClass:[GBVideoEncoderGenCppProxy class]]) {
        return ((GBVideoEncoderGenCppProxy*)objc)->_cppRefHandle.get();
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto VideoEncoderGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    if (auto cppPtr = dynamic_cast<ObjcProxy*>(cpp.get())) {
        return cppPtr->Handle::get();
    }
    return ::djinni::get_cpp_proxy<GBVideoEncoderGenCppProxy>(cpp);
}

}  // namespace djinni_generated

@end
