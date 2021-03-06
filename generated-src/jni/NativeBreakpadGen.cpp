// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "NativeBreakpadGen.hpp"  // my header
#include "NativeCrashHandlerGen.hpp"

namespace djinni_generated {

NativeBreakpadGen::NativeBreakpadGen() : ::djinni::JniInterface<::gearsbox::BreakpadGen, NativeBreakpadGen>("dyno/fun/gearsbox/BreakpadGen$CppProxy") {}

NativeBreakpadGen::~NativeBreakpadGen() = default;


CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_BreakpadGen_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::gearsbox::BreakpadGen>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_BreakpadGen_00024CppProxy_native_1start(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::BreakpadGen>(nativeRef);
        ref->start();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_BreakpadGen_00024CppProxy_native_1stop(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::BreakpadGen>(nativeRef);
        ref->stop();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_BreakpadGen_00024CppProxy_native_1setUploadUrl(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::BreakpadGen>(nativeRef);
        ref->setUploadUrl();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_BreakpadGen_00024CppProxy_native_1setHandler(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_hander)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::BreakpadGen>(nativeRef);
        ref->setHandler(::djinni_generated::NativeCrashHandlerGen::toCpp(jniEnv, j_hander));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated
