// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include "djinni_support.hpp"
#include "text_keyboard.hpp"

namespace djinni_generated {

class NativeTextKeyboard final : ::djinni::JniEnum {
public:
    using CppType = ::gearsbox::TextKeyboard;
    using JniType = jobject;

    using Boxed = NativeTextKeyboard;

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return static_cast<CppType>(::djinni::JniClass<NativeTextKeyboard>::get().ordinal(jniEnv, j)); }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, CppType c) { return ::djinni::JniClass<NativeTextKeyboard>::get().create(jniEnv, static_cast<jint>(c)); }

private:
    NativeTextKeyboard() : JniEnum("dyno/fun/gearsbox/TextKeyboard") {}
    friend ::djinni::JniClass<NativeTextKeyboard>;
};

}  // namespace djinni_generated
