// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "NativeUiManagerGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeUiManagerGen.hpp"
#include "NativeViewFactoryGen.hpp"
#include "NativeViewGen.hpp"

namespace djinni_generated {

NativeUiManagerGen::NativeUiManagerGen() : ::djinni::JniInterface<::gearsbox::UiManagerGen, NativeUiManagerGen>("dyno/fun/gearsbox/UiManagerGen$CppProxy") {}

NativeUiManagerGen::~NativeUiManagerGen() = default;


CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_UiManagerGen_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::gearsbox::UiManagerGen>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_UiManagerGen_instance(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::gearsbox::UiManagerGen::instance();
        return ::djinni::release(::djinni_generated::NativeUiManagerGen::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_dyno_fun_gearsbox_UiManagerGen_00024CppProxy_native_1initialize(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_param, jobject j_factory)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::UiManagerGen>(nativeRef);
        auto r = ref->initialize(::djinni::String::toCpp(jniEnv, j_param),
                                 ::djinni_generated::NativeViewFactoryGen::toCpp(jniEnv, j_factory));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_UiManagerGen_00024CppProxy_native_1inject(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_id, jobject j_view)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::UiManagerGen>(nativeRef);
        ref->inject(::djinni::String::toCpp(jniEnv, j_id),
                    ::djinni_generated::NativeViewGen::toCpp(jniEnv, j_view));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_UiManagerGen_00024CppProxy_native_1getView(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_id)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::UiManagerGen>(nativeRef);
        auto r = ref->getView(::djinni::String::toCpp(jniEnv, j_id));
        return ::djinni::release(::djinni_generated::NativeViewGen::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_UiManagerGen_00024CppProxy_native_1removeView(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_id)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::UiManagerGen>(nativeRef);
        ref->removeView(::djinni::String::toCpp(jniEnv, j_id));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated