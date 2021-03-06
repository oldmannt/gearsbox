// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include "djinni_support.hpp"
#include "lang_type.hpp"

namespace djinni_generated {

class NativeLangType final : ::djinni::JniEnum {
public:
    using CppType = ::gearsbox::LangType;
    using JniType = jobject;

    using Boxed = NativeLangType;

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return static_cast<CppType>(::djinni::JniClass<NativeLangType>::get().ordinal(jniEnv, j)); }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, CppType c) { return ::djinni::JniClass<NativeLangType>::get().create(jniEnv, static_cast<jint>(c)); }

private:
    NativeLangType() : JniEnum("dyno/fun/gearsbox/LangType") {}
    friend ::djinni::JniClass<NativeLangType>;
};

}  // namespace djinni_generated
