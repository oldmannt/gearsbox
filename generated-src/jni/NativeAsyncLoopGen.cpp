// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "NativeAsyncLoopGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeAsyncLoopGen.hpp"

namespace djinni_generated {

NativeAsyncLoopGen::NativeAsyncLoopGen() : ::djinni::JniInterface<::gearsbox::AsyncLoopGen, NativeAsyncLoopGen>("dyno/fun/gearsbox/AsyncLoopGen$CppProxy") {}

NativeAsyncLoopGen::~NativeAsyncLoopGen() = default;


CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_AsyncLoopGen_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::gearsbox::AsyncLoopGen>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_AsyncLoopGen_instance(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::gearsbox::AsyncLoopGen::instance();
        return ::djinni::release(::djinni_generated::NativeAsyncLoopGen::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_AsyncLoopGen_00024CppProxy_native_1process(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jlong j_elapse)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::AsyncLoopGen>(nativeRef);
        ref->process(::djinni::I64::toCpp(jniEnv, j_elapse));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated
