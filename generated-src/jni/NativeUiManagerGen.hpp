// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include "djinni_support.hpp"
#include "ui_manager_gen.hpp"

namespace djinni_generated {

class NativeUiManagerGen final : ::djinni::JniInterface<::gearsbox::UiManagerGen, NativeUiManagerGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::UiManagerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::UiManagerGen>;
    using JniType = jobject;

    using Boxed = NativeUiManagerGen;

    ~NativeUiManagerGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeUiManagerGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeUiManagerGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeUiManagerGen();
    friend ::djinni::JniClass<NativeUiManagerGen>;
    friend ::djinni::JniInterface<::gearsbox::UiManagerGen, NativeUiManagerGen>;

};

}  // namespace djinni_generated