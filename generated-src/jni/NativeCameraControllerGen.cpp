// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#include "NativeCameraControllerGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeCameraCaptureHandler.hpp"
#include "NativeCameraCaptureMode.hpp"
#include "NativeCameraExposureMode.hpp"
#include "NativeCameraFlash.hpp"
#include "NativeCameraFocusMode.hpp"
#include "NativeCameraFocusRange.hpp"
#include "NativeCameraQuality.hpp"
#include "NativeDuration.hpp"
#include "NativeVideoFrameGen.hpp"

namespace djinni_generated {

NativeCameraControllerGen::NativeCameraControllerGen() : ::djinni::JniInterface<::gearsbox::CameraControllerGen, NativeCameraControllerGen>() {}

NativeCameraControllerGen::~NativeCameraControllerGen() = default;

NativeCameraControllerGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeCameraControllerGen::JavaProxy::~JavaProxy() = default;

void NativeCameraControllerGen::JavaProxy::initialize(bool c_audio) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_initialize,
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_audio)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::setAudioEnable(bool c_enable) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setAudioEnable,
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_enable)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::startCamera() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_startCamera);
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::stopCamera() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_stopCamera);
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::switchFront(bool c_front) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_switchFront,
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_front)));
    ::djinni::jniExceptionCheck(jniEnv);
}
bool NativeCameraControllerGen::JavaProxy::isFront() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_isFront);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setFlashMode(::gearsbox::CameraFlash c_mode) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFlashMode,
                           ::djinni::get(::djinni_generated::NativeCameraFlash::fromCpp(jniEnv, c_mode)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::CameraFlash NativeCameraControllerGen::JavaProxy::getFlashMode() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getFlashMode);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeCameraFlash::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setQuality(::gearsbox::CameraQuality c_quality) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setQuality,
                           ::djinni::get(::djinni_generated::NativeCameraQuality::fromCpp(jniEnv, c_quality)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::CameraQuality NativeCameraControllerGen::JavaProxy::getQuality() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getQuality);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeCameraQuality::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setSloMo(bool c_flag) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setSloMo,
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_flag)));
    ::djinni::jniExceptionCheck(jniEnv);
}
bool NativeCameraControllerGen::JavaProxy::getSloMo() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_getSloMo);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}
int32_t NativeCameraControllerGen::JavaProxy::getMaxFrameRate() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getMaxFrameRate);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
int32_t NativeCameraControllerGen::JavaProxy::getDefaultFrameRate() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getDefaultFrameRate);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setFrameDuration(int64_t c_value, int32_t c_scale) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFrameDuration,
                           ::djinni::get(::djinni::I64::fromCpp(jniEnv, c_value)),
                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_scale)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::setFrameDurationRange(const ::gearsbox::Duration & c_min, const ::gearsbox::Duration & c_max) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFrameDurationRange,
                           ::djinni::get(::djinni_generated::NativeDuration::fromCpp(jniEnv, c_min)),
                           ::djinni::get(::djinni_generated::NativeDuration::fromCpp(jniEnv, c_max)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::Duration NativeCameraControllerGen::JavaProxy::getFrameDuration() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getFrameDuration);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeDuration::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setExposureMode(::gearsbox::CameraExposureMode c_mode) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setExposureMode,
                           ::djinni::get(::djinni_generated::NativeCameraExposureMode::fromCpp(jniEnv, c_mode)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::CameraExposureMode NativeCameraControllerGen::JavaProxy::getExposureMode() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getExposureMode);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeCameraExposureMode::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setExposurePoint(float c_x, float c_y) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setExposurePoint,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_x)),
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_y)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::setExposureEv(float c_ev) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setExposureEv,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_ev)));
    ::djinni::jniExceptionCheck(jniEnv);
}
float NativeCameraControllerGen::JavaProxy::getExposureEv() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getExposureEv);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getExposureMaxEv() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getExposureMaxEv);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getExposureMinEv() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getExposureMinEv);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setExposureDuration(float c_seconds) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setExposureDuration,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_seconds)));
    ::djinni::jniExceptionCheck(jniEnv);
}
float NativeCameraControllerGen::JavaProxy::getExposureDuration() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getExposureDuration);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getExposureMinDuration() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getExposureMinDuration);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getExposureMaxDuration() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getExposureMaxDuration);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setISO(int32_t c_iso) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setISO,
                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_iso)));
    ::djinni::jniExceptionCheck(jniEnv);
}
int32_t NativeCameraControllerGen::JavaProxy::getISO() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getISO);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
int32_t NativeCameraControllerGen::JavaProxy::getISOMax() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getISOMax);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
int32_t NativeCameraControllerGen::JavaProxy::getISOMin() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallIntMethod(Handle::get().get(), data.method_getISOMin);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::I32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getEV() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getEV);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setEV(float c_ev) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setEV,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_ev)));
    ::djinni::jniExceptionCheck(jniEnv);
}
float NativeCameraControllerGen::JavaProxy::getEVMax() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getEVMax);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getEVMin() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getEVMin);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setFocusMode(::gearsbox::CameraFocusMode c_mode) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFocusMode,
                           ::djinni::get(::djinni_generated::NativeCameraFocusMode::fromCpp(jniEnv, c_mode)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::CameraFocusMode NativeCameraControllerGen::JavaProxy::getFocusMode() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getFocusMode);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeCameraFocusMode::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setFocusLens(float c_lens) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFocusLens,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_lens)));
    ::djinni::jniExceptionCheck(jniEnv);
}
float NativeCameraControllerGen::JavaProxy::getFocusLens() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getFocusLens);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getFocusMax() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getFocusMax);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getFocusMin() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getFocusMin);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setFocusPoint(float c_x, float c_y) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFocusPoint,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_x)),
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_y)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::setFocusAutoRange(::gearsbox::CameraFocusRange c_range) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFocusAutoRange,
                           ::djinni::get(::djinni_generated::NativeCameraFocusRange::fromCpp(jniEnv, c_range)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::CameraFocusRange NativeCameraControllerGen::JavaProxy::getFocusAutoRange() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getFocusAutoRange);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeCameraFocusRange::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setZoom(float c_zoom) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setZoom,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_zoom)));
    ::djinni::jniExceptionCheck(jniEnv);
}
float NativeCameraControllerGen::JavaProxy::getZoom() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getZoom);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getZoomMax() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getZoomMax);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
float NativeCameraControllerGen::JavaProxy::getZoomMin() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallFloatMethod(Handle::get().get(), data.method_getZoomMin);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::F32::toCpp(jniEnv, jret);
}
std::shared_ptr<::gearsbox::VideoFrameGen> NativeCameraControllerGen::JavaProxy::captureOneFrame() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_captureOneFrame);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeVideoFrameGen::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::asnyOneFrame() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_asnyOneFrame);
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::asnyOnePicture() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_asnyOnePicture);
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::setCaptureHandler(const std::shared_ptr<::gearsbox::CameraCaptureHandler> & c_handler) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setCaptureHandler,
                           ::djinni::get(::djinni_generated::NativeCameraCaptureHandler::fromCpp(jniEnv, c_handler)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeCameraControllerGen::JavaProxy::setCaptureMode(::gearsbox::CameraCaptureMode c_mode) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setCaptureMode,
                           ::djinni::get(::djinni_generated::NativeCameraCaptureMode::fromCpp(jniEnv, c_mode)));
    ::djinni::jniExceptionCheck(jniEnv);
}
::gearsbox::CameraCaptureMode NativeCameraControllerGen::JavaProxy::getCaptureMode() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_getCaptureMode);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeCameraCaptureMode::toCpp(jniEnv, jret);
}
void NativeCameraControllerGen::JavaProxy::setImmediaPause(bool c_flag) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setImmediaPause,
                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c_flag)));
    ::djinni::jniExceptionCheck(jniEnv);
}
std::string NativeCameraControllerGen::JavaProxy::getDebugInfo() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeCameraControllerGen>::get();
    auto jret = (jstring)jniEnv->CallObjectMethod(Handle::get().get(), data.method_getDebugInfo);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::String::toCpp(jniEnv, jret);
}

}  // namespace djinni_generated
