// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "NativeFileInfoGen.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeFileInfoGen::NativeFileInfoGen() : ::djinni::JniInterface<::gearsbox::FileInfoGen, NativeFileInfoGen>() {}

NativeFileInfoGen::~NativeFileInfoGen() = default;

NativeFileInfoGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeFileInfoGen::JavaProxy::~JavaProxy() = default;

bool NativeFileInfoGen::JavaProxy::initialize(const std::string & c_path) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_initialize,
                                          ::djinni::get(::djinni::String::fromCpp(jniEnv, c_path)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}
int64_t NativeFileInfoGen::JavaProxy::getSize() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = jniEnv->CallLongMethod(Handle::get().get(), data.method_getSize);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I64::toCpp(jniEnv, jret);
}
std::chrono::system_clock::time_point NativeFileInfoGen::JavaProxy::getCreateDate() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getCreateDate);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Date::toCpp(jniEnv, jret);
}
std::string NativeFileInfoGen::JavaProxy::getName() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getName);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}
std::string NativeFileInfoGen::JavaProxy::getSuffix() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getSuffix);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}
std::string NativeFileInfoGen::JavaProxy::getPrefix() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getPrefix);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}
std::string NativeFileInfoGen::JavaProxy::getPath() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeFileInfoGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getPath);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}

}  // namespace djinni_generated