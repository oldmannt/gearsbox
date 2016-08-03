// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBInstanceGetterGen+Private.h"
#import "GBInstanceGetterGen.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "GBCameraControllerGen+Private.h"
#import "GBConfigGen+Private.h"
#import "GBPlatformUtilityGen+Private.h"
#include <exception>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface GBInstanceGetterGen ()

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::InstanceGetterGen>&)cppRef;

@end

@implementation GBInstanceGetterGen {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::gearsbox::InstanceGetterGen>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::InstanceGetterGen>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

+ (nullable id<GBCameraControllerGen>)getCameraController {
    try {
        auto r = ::gearsbox::InstanceGetterGen::getCameraController();
        return ::djinni_generated::CameraControllerGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (void)setCameraController:(nullable id<GBCameraControllerGen>)camera {
    try {
        ::gearsbox::InstanceGetterGen::setCameraController(::djinni_generated::CameraControllerGen::toCpp(camera));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (nullable id<GBPlatformUtilityGen>)getPlatformUtility {
    try {
        auto r = ::gearsbox::InstanceGetterGen::getPlatformUtility();
        return ::djinni_generated::PlatformUtilityGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (void)setPlatformUtility:(nullable id<GBPlatformUtilityGen>)mgr {
    try {
        ::gearsbox::InstanceGetterGen::setPlatformUtility(::djinni_generated::PlatformUtilityGen::toCpp(mgr));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (nullable GBConfigGen *)getConfig:(nonnull NSString *)id {
    try {
        auto r = ::gearsbox::InstanceGetterGen::getConfig(::djinni::String::toCpp(id));
        return ::djinni_generated::ConfigGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace djinni_generated {

auto InstanceGetterGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto InstanceGetterGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<GBInstanceGetterGen>(cpp);
}

}  // namespace djinni_generated

@end
