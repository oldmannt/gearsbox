// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#include "NativeVideoFrameGen.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeVideoFrameGen::NativeVideoFrameGen() : ::djinni::JniInterface<::gearsbox::VideoFrameGen, NativeVideoFrameGen>() {}

NativeVideoFrameGen::~NativeVideoFrameGen() = default;

NativeVideoFrameGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeVideoFrameGen::JavaProxy::~JavaProxy() = default;

int64_t NativeVideoFrameGen::JavaProxy::getData() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoFrameGen>::get();
    auto jret = jniEnv->CallLongMethod(Handle::get().get(), data.method_getData);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I64::toCpp(jniEnv, jret);
}
int32_t NativeVideoFrameGen::JavaProxy::getWidth() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoFrameGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getWidth);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
int32_t NativeVideoFrameGen::JavaProxy::getHeight() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoFrameGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getHeight);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
int64_t NativeVideoFrameGen::JavaProxy::getSize() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoFrameGen>::get();
    auto jret = jniEnv->CallLongMethod(Handle::get().get(), data.method_getSize);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I64::toCpp(jniEnv, jret);
}

}  // namespace djinni_generated