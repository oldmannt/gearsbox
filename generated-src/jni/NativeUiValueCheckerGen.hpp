// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include "djinni_support.hpp"
#include "ui_value_checker_gen.hpp"

namespace djinni_generated {

class NativeUiValueCheckerGen final : ::djinni::JniInterface<::gearsbox::UiValueCheckerGen, NativeUiValueCheckerGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::UiValueCheckerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::UiValueCheckerGen>;
    using JniType = jobject;

    using Boxed = NativeUiValueCheckerGen;

    ~NativeUiValueCheckerGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeUiValueCheckerGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeUiValueCheckerGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeUiValueCheckerGen();
    friend ::djinni::JniClass<NativeUiValueCheckerGen>;
    friend ::djinni::JniInterface<::gearsbox::UiValueCheckerGen, NativeUiValueCheckerGen>;

};

}  // namespace djinni_generated