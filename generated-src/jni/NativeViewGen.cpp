// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "NativeViewGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeArgbColor.hpp"
#include "NativeViewConf.hpp"
#include "NativeViewConstraint.hpp"
#include "NativeViewEvent.hpp"
#include "NativeViewEventHandler.hpp"
#include "NativeViewFrame.hpp"
#include "NativeViewGen.hpp"
#include "NativeViewType.hpp"

namespace djinni_generated {

NativeViewGen::NativeViewGen() : ::djinni::JniInterface<::gearsbox::ViewGen, NativeViewGen>() {}

NativeViewGen::~NativeViewGen() = default;

NativeViewGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeViewGen::JavaProxy::~JavaProxy() = default;

std::string NativeViewGen::JavaProxy::getId() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getId);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}
void NativeViewGen::JavaProxy::setFrame(const ::gearsbox::ViewFrame & c_frame) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFrame,
                           ::djinni::get(::djinni_generated::NativeViewFrame::fromCpp(jniEnv, c_frame)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::ViewFrame NativeViewGen::JavaProxy::getFrame() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getFrame);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewFrame::toCpp(jniEnv, jret);
}
void NativeViewGen::JavaProxy::setBackgroundColor(float c_a, float c_r, float c_g, float c_b) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setBackgroundColor,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_a)),
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_r)),
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_g)),
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_b)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::setVisiable(bool c_v) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setVisiable,
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_v)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::ViewType NativeViewGen::JavaProxy::getType() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getType);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewType::toCpp(jniEnv, jret);
}
void NativeViewGen::JavaProxy::setBoard(float c_width, const ::gearsbox::ArgbColor & c_color) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setBoard,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_width)),
                           ::djinni::get(::djinni_generated::NativeArgbColor::fromCpp(jniEnv, c_color)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::setText(const std::string & c_text) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setText,
                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c_text)));
    ::djinni::jniExceptionCheck(jniEnv);
}
std::string NativeViewGen::JavaProxy::getText() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getText);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}
void NativeViewGen::JavaProxy::setTextColor(const ::gearsbox::ArgbColor & c_color) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setTextColor,
                           ::djinni::get(::djinni_generated::NativeArgbColor::fromCpp(jniEnv, c_color)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::setFontSize(int32_t c_size) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFontSize,
                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_size)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::setNumbernic(int32_t c_type) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setNumbernic,
                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_type)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::setMaxTextLen(int32_t c_length) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setMaxTextLen,
                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_length)));
    ::djinni::jniExceptionCheck(jniEnv);
}
std::shared_ptr<::gearsbox::ViewGen> NativeViewGen::JavaProxy::getSubView(const std::string & c_id) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getSubView,
                                         ::djinni::get(::djinni::String::fromCpp(jniEnv, c_id)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewGen::toCpp(jniEnv, jret);
}
std::shared_ptr<::gearsbox::ViewGen> NativeViewGen::JavaProxy::addSubViewById(const std::string & c_id, ::gearsbox::ViewType c_type) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_addSubViewById,
                                         ::djinni::get(::djinni::String::fromCpp(jniEnv, c_id)),
                                         ::djinni::get(::djinni_generated::NativeViewType::fromCpp(jniEnv, c_type)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewGen::toCpp(jniEnv, jret);
}
std::shared_ptr<::gearsbox::ViewGen> NativeViewGen::JavaProxy::addSubView(const ::gearsbox::ViewConf & c_conf) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_addSubView,
                                         ::djinni::get(::djinni_generated::NativeViewConf::fromCpp(jniEnv, c_conf)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeViewGen::toCpp(jniEnv, jret);
}
bool NativeViewGen::JavaProxy::removeSubView(const std::string & c_id) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_removeSubView,
                                          ::djinni::get(::djinni::String::fromCpp(jniEnv, c_id)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}
void NativeViewGen::JavaProxy::removeAllSubView() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_removeAllSubView);
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::addConstraint(const ::gearsbox::ViewConstraint & c_constraint) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_addConstraint,
                           ::djinni::get(::djinni_generated::NativeViewConstraint::fromCpp(jniEnv, c_constraint)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeViewGen::JavaProxy::setEventHandler(::gearsbox::ViewEvent c_event, const std::shared_ptr<::gearsbox::ViewEventHandler> & c_handler) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeViewGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setEventHandler,
                           ::djinni::get(::djinni_generated::NativeViewEvent::fromCpp(jniEnv, c_event)),
                           ::djinni::get(::djinni_generated::NativeViewEventHandler::fromCpp(jniEnv, c_handler)));
    ::djinni::jniExceptionCheck(jniEnv);
}

}  // namespace djinni_generated
