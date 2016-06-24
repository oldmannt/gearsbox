// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#import "GBUiManagerGen+Private.h"
#import "GBUiManagerGen.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "GBUiManagerGen+Private.h"
#import "GBViewFactoryGen+Private.h"
#import "GBViewGen+Private.h"
#include <exception>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface GBUiManagerGen ()

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::UiManagerGen>&)cppRef;

@end

@implementation GBUiManagerGen {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::gearsbox::UiManagerGen>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::UiManagerGen>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

+ (nullable GBUiManagerGen *)instance {
    try {
        auto r = ::gearsbox::UiManagerGen::instance();
        return ::djinni_generated::UiManagerGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (BOOL)initialize:(nonnull NSString *)param
           factory:(nullable id<GBViewFactoryGen>)factory {
    try {
        auto r = _cppRefHandle.get()->initialize(::djinni::String::toCpp(param),
                                                 ::djinni_generated::ViewFactoryGen::toCpp(factory));
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)inject:(nullable id<GBViewGen>)view {
    try {
        _cppRefHandle.get()->inject(::djinni_generated::ViewGen::toCpp(view));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nullable id<GBViewGen>)getView:(nonnull NSString *)id {
    try {
        auto r = _cppRefHandle.get()->getView(::djinni::String::toCpp(id));
        return ::djinni_generated::ViewGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (BOOL)addView:(nullable id<GBViewGen>)view {
    try {
        auto r = _cppRefHandle.get()->addView(::djinni_generated::ViewGen::toCpp(view));
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)removeView:(nonnull NSString *)id {
    try {
        _cppRefHandle.get()->removeView(::djinni::String::toCpp(id));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace djinni_generated {

auto UiManagerGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto UiManagerGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<GBUiManagerGen>(cpp);
}

}  // namespace djinni_generated

@end
