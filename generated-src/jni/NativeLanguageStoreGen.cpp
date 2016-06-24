// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "NativeLanguageStoreGen.hpp"  // my header
#include "Marshal.hpp"
#include "NativeLangType.hpp"
#include "NativeLanguageStoreGen.hpp"

namespace djinni_generated {

NativeLanguageStoreGen::NativeLanguageStoreGen() : ::djinni::JniInterface<::gearsbox::LanguageStoreGen, NativeLanguageStoreGen>("dyno/fun/gearsbox/LanguageStoreGen$CppProxy") {}

NativeLanguageStoreGen::~NativeLanguageStoreGen() = default;


CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_LanguageStoreGen_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::gearsbox::LanguageStoreGen>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_LanguageStoreGen_instance(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::gearsbox::LanguageStoreGen::instance();
        return ::djinni::release(::djinni_generated::NativeLanguageStoreGen::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_dyno_fun_gearsbox_LanguageStoreGen_00024CppProxy_native_1initialize(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_param)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::LanguageStoreGen>(nativeRef);
        auto r = ref->initialize(::djinni::String::toCpp(jniEnv, j_param));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_dyno_fun_gearsbox_LanguageStoreGen_00024CppProxy_native_1setLanguage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_lang)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::LanguageStoreGen>(nativeRef);
        ref->setLanguage(::djinni_generated::NativeLangType::toCpp(jniEnv, j_lang));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_dyno_fun_gearsbox_LanguageStoreGen_00024CppProxy_native_1getLanguage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::LanguageStoreGen>(nativeRef);
        auto r = ref->getLanguage();
        return ::djinni::release(::djinni_generated::NativeLangType::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_dyno_fun_gearsbox_LanguageStoreGen_00024CppProxy_native_1getString(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_type)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::gearsbox::LanguageStoreGen>(nativeRef);
        auto r = ref->getString(::djinni::String::toCpp(jniEnv, j_type));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated
