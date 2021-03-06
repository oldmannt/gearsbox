// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "NativeViewFactoryGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeViewConf.hpp"
#include "NativeViewGen.hpp"
#include "NativeViewType.hpp"

namespace djinni_generated {

NativeViewFactoryGen::NativeViewFactoryGen() : ::djinni::JniInterface<::gearsbox::ViewFactoryGen, NativeViewFactoryGen>() {}

NativeViewFactoryGen::~NativeViewFactoryGen() = default;

NativeViewFactoryGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeViewFactoryGen::JavaProxy::~JavaProxy() = default;

std::shared_ptr<::gearsbox::ViewGen> NativeViewFactoryGen::JavaProxy::createView(const ::gearsbox::ViewConf & c_conf) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewFactoryGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_createView,
                                         ::djinni::get(::djinni_generated::NativeViewConf::fromCpp(jniEnv, c_conf)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewGen::toCpp(jniEnv, jret);
}
std::shared_ptr<::gearsbox::ViewGen> NativeViewFactoryGen::JavaProxy::createViewById(const std::string & c_id, ::gearsbox::ViewType c_type) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewFactoryGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_createViewById,
                                         ::djinni::get(::djinni::String::fromCpp(jniEnv, c_id)),
                                         ::djinni::get(::djinni_generated::NativeViewType::fromCpp(jniEnv, c_type)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewGen::toCpp(jniEnv, jret);
}
bool NativeViewFactoryGen::JavaProxy::injectView(const std::shared_ptr<::gearsbox::ViewGen> & c_view) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewFactoryGen>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_injectView,
                                          ::djinni::get(::djinni_generated::NativeViewGen::fromCpp(jniEnv, c_view)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}
void NativeViewFactoryGen::JavaProxy::showViewController(const std::string & c_id, bool c_animated) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewFactoryGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_showViewController,
                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c_id)),
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_animated)));
    ::djinni::jniExceptionCheck(jniEnv);
}

}  // namespace djinni_generated
