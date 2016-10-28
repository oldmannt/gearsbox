// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBTaskManagerGen+Private.h"
#import "GBTaskManagerGen.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "GBTaskExcuserGen+Private.h"
#import "GBTaskInfoGen+Private.h"
#import "GBTaskManagerGen+Private.h"
#include <exception>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface GBTaskManagerGen ()

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::TaskManagerGen>&)cppRef;

@end

@implementation GBTaskManagerGen {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::gearsbox::TaskManagerGen>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::gearsbox::TaskManagerGen>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

+ (nullable GBTaskManagerGen *)instance {
    try {
        auto r = ::gearsbox::TaskManagerGen::instance();
        return ::djinni_generated::TaskManagerGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (nullable id<GBTaskInfoGen>)createInfo:(int64_t)taskId
                                   delay:(int64_t)delay
                                repeated:(int32_t)repeated {
    try {
        auto r = ::gearsbox::TaskManagerGen::create_info(::djinni::I64::toCpp(taskId),
                                                         ::djinni::I64::toCpp(delay),
                                                         ::djinni::I32::toCpp(repeated));
        return ::djinni_generated::TaskInfoGen::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)addTask:(int64_t)taskId
          delay:(int64_t)delay
       repeated:(int32_t)repeated
           task:(nullable id<GBTaskExcuserGen>)task {
    try {
        _cppRefHandle.get()->addTask(::djinni::I64::toCpp(taskId),
                                     ::djinni::I64::toCpp(delay),
                                     ::djinni::I32::toCpp(repeated),
                                     ::djinni_generated::TaskExcuserGen::toCpp(task));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)addTaskI:(int64_t)taskId
            task:(nullable id<GBTaskExcuserGen>)task {
    try {
        _cppRefHandle.get()->addTaskI(::djinni::I64::toCpp(taskId),
                                      ::djinni_generated::TaskExcuserGen::toCpp(task));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)addTaskInfo:(nullable id<GBTaskInfoGen>)task
        taskExcuser:(nullable id<GBTaskExcuserGen>)taskExcuser {
    try {
        _cppRefHandle.get()->addTaskInfo(::djinni_generated::TaskInfoGen::toCpp(task),
                                         ::djinni_generated::TaskExcuserGen::toCpp(taskExcuser));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)addTaskExcuser:(nullable id<GBTaskExcuserGen>)task {
    try {
        _cppRefHandle.get()->addTaskExcuser(::djinni_generated::TaskExcuserGen::toCpp(task));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)removeTask:(int64_t)taskId {
    try {
        _cppRefHandle.get()->removeTask(::djinni::I64::toCpp(taskId));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace djinni_generated {

auto TaskManagerGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto TaskManagerGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<GBTaskManagerGen>(cpp);
}

}  // namespace djinni_generated

@end
