// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "NativeDeviceGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeDeviceOrientation.hpp"

namespace djinni_generated {

NativeDeviceGen::NativeDeviceGen() : ::djinni::JniInterface<::gearsbox::DeviceGen, NativeDeviceGen>() {}

NativeDeviceGen::~NativeDeviceGen() = default;

NativeDeviceGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeDeviceGen::JavaProxy::~JavaProxy() = default;

::gearsbox::DeviceOrientation NativeDeviceGen::JavaProxy::getOrientation() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeDeviceGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getOrientation);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeDeviceOrientation::toCpp(jniEnv, jret);
}
std::string NativeDeviceGen::JavaProxy::getID() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeDeviceGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getID);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}

}  // namespace djinni_generated
