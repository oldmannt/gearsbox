// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "NativeInstanceGetterGen.hpp"  // my header
#include "NativeCameraControllerGen.hpp"
#include "NativePlatformUtilityGen.hpp"

namespace djinni_generated {

NativeInstanceGetterGen::NativeInstanceGetterGen() : ::djinni::JniInterface<::gearsbox::InstanceGetterGen, NativeInstanceGetterGen>("dyno/fun/gearsbox/InstanceGetterGen$CppProxy") {}

NativeInstanceGetterGen::~NativeInstanceGetterGen() = default;


CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_InstanceGetterGen_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::gearsbox::InstanceGetterGen>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_InstanceGetterGen_getCameraController(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::gearsbox::InstanceGetterGen::getCameraController();
        return ::djinni::release(::djinni_generated::NativeCameraControllerGen::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_InstanceGetterGen_setCameraController(JNIEnv* jniEnv, jobject /*this*/, jobject j_camera)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::gearsbox::InstanceGetterGen::setCameraController(::djinni_generated::NativeCameraControllerGen::toCpp(jniEnv, j_camera));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_InstanceGetterGen_getPlatformUtility(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::gearsbox::InstanceGetterGen::getPlatformUtility();
        return ::djinni::release(::djinni_generated::NativePlatformUtilityGen::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_InstanceGetterGen_setPlatformUtility(JNIEnv* jniEnv, jobject /*this*/, jobject j_mgr)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::gearsbox::InstanceGetterGen::setPlatformUtility(::djinni_generated::NativePlatformUtilityGen::toCpp(jniEnv, j_mgr));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated