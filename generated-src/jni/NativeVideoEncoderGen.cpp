// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#include "NativeVideoEncoderGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeVideoFrameGen.hpp"
#include "NativeVideoOrientation.hpp"

namespace djinni_generated {

NativeVideoEncoderGen::NativeVideoEncoderGen() : ::djinni::JniInterface<::gearsbox::VideoEncoderGen, NativeVideoEncoderGen>("dyno/fun/gearsbox/VideoEncoderGen$CppProxy") {}

NativeVideoEncoderGen::~NativeVideoEncoderGen() = default;

NativeVideoEncoderGen::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeVideoEncoderGen::JavaProxy::~JavaProxy() = default;

bool NativeVideoEncoderGen::JavaProxy::initialize(const std::string & c_filepath, int32_t c_fps, int32_t c_bitrate, ::gearsbox::VideoOrientation c_ori, int32_t c_width, int32_t c_height, const std::shared_ptr<::gearsbox::VideoFrameGen> & c_frame) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoEncoderGen>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_initialize,
                                          ::djinni::get(::djinni::String::fromCpp(jniEnv, c_filepath)),
                                          ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_fps)),
                                          ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_bitrate)),
                                          ::djinni::get(::djinni_generated::NativeVideoOrientation::fromCpp(jniEnv, c_ori)),
                                          ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_width)),
                                          ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_height)),
                                          ::djinni::get(::djinni_generated::NativeVideoFrameGen::fromCpp(jniEnv, c_frame)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}
void NativeVideoEncoderGen::JavaProxy::encodeFrame(const std::shared_ptr<::gearsbox::VideoFrameGen> & c_frame) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoEncoderGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_encodeFrame,
                           ::djinni::get(::djinni_generated::NativeVideoFrameGen::fromCpp(jniEnv, c_frame)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeVideoEncoderGen::JavaProxy::setFps(int32_t c_fps) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoEncoderGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setFps,
                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c_fps)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeVideoEncoderGen::JavaProxy::saveNRelease() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeVideoEncoderGen>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_saveNRelease);
    ::djinni::jniExceptionCheck(jniEnv);
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_VideoEncoderGen_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::gearsbox::VideoEncoderGen>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jboolean JNICALL Java_dyno_fun_gearsbox_VideoEncoderGen_00024CppProxy_native_1initialize(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_filepath, jint j_fps, jint j_bitrate, jobject j_ori, jint j_width, jint j_height, jobject j_frame)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::VideoEncoderGen>(nativeRef);
        auto r = ref->initialize(::djinni::String::toCpp(jniEnv, j_filepath),
                                 ::djinni::I32::toCpp(jniEnv, j_fps),
                                 ::djinni::I32::toCpp(jniEnv, j_bitrate),
                                 ::djinni_generated::NativeVideoOrientation::toCpp(jniEnv, j_ori),
                                 ::djinni::I32::toCpp(jniEnv, j_width),
                                 ::djinni::I32::toCpp(jniEnv, j_height),
                                 ::djinni_generated::NativeVideoFrameGen::toCpp(jniEnv, j_frame));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_VideoEncoderGen_00024CppProxy_native_1encodeFrame(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_frame)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::VideoEncoderGen>(nativeRef);
        ref->encodeFrame(::djinni_generated::NativeVideoFrameGen::toCpp(jniEnv, j_frame));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_VideoEncoderGen_00024CppProxy_native_1setFps(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jint j_fps)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::VideoEncoderGen>(nativeRef);
        ref->setFps(::djinni::I32::toCpp(jniEnv, j_fps));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_VideoEncoderGen_00024CppProxy_native_1saveNRelease(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::VideoEncoderGen>(nativeRef);
        ref->saveNRelease();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated
