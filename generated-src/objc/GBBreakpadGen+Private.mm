// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBBreakpadGen+Private.h"
#import "GBBreakpadGen.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIObjcWrapperCache+Private.h"
#import "GBCrashHandlerGen+Private.h"
#include <exception>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface GBBreakpadGenCppProxy : NSObject<GBBreakpadGen>

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::BreakpadGen>&)cppRef;

@end

@implementation GBBreakpadGenCppProxy {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::gearsbox::BreakpadGen>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::BreakpadGen>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

- (void)start {
    try {
        _cppRefHandle.get()->start();
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)stop {
    try {
        _cppRefHandle.get()->stop();
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)setUploadUrl {
    try {
        _cppRefHandle.get()->setUploadUrl();
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)setHandler:(nullable id<GBCrashHandlerGen>)hander {
    try {
        _cppRefHandle.get()->setHandler(::djinni_generated::CrashHandlerGen::toCpp(hander));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace djinni_generated {

class BreakpadGen::ObjcProxy final
: public ::gearsbox::BreakpadGen
, public ::djinni::ObjcProxyCache::Handle<ObjcType>
{
public:
    using Handle::Handle;
    void start() override
    {
        @autoreleasepool {
            [Handle::get() start];
        }
    }
    void stop() override
    {
        @autoreleasepool {
            [Handle::get() stop];
        }
    }
    void setUploadUrl() override
    {
        @autoreleasepool {
            [Handle::get() setUploadUrl];
        }
    }
    void setHandler(const std::shared_ptr<::gearsbox::CrashHandlerGen> & c_hander) override
    {
        @autoreleasepool {
            [Handle::get() setHandler:(::djinni_generated::CrashHandlerGen::fromCpp(c_hander))];
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto BreakpadGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    if ([(id)objc isKindOfClass:[GBBreakpadGenCppProxy class]]) {
        return ((GBBreakpadGenCppProxy*)objc)->_cppRefHandle.get();
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto BreakpadGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    if (auto cppPtr = dynamic_cast<ObjcProxy*>(cpp.get())) {
        return cppPtr->Handle::get();
    }
    return ::djinni::get_cpp_proxy<GBBreakpadGenCppProxy>(cpp);
}

}  // namespace djinni_generated

@end
