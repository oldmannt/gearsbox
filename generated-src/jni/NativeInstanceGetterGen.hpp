// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include "djinni_support.hpp"
#include "instance_getter_gen.hpp"

namespace djinni_generated {

class NativeInstanceGetterGen final : ::djinni::JniInterface<::gearsbox::InstanceGetterGen, NativeInstanceGetterGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::InstanceGetterGen>;
    using CppOptType = std::shared_ptr<::gearsbox::InstanceGetterGen>;
    using JniType = jobject;

    using Boxed = NativeInstanceGetterGen;

    ~NativeInstanceGetterGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeInstanceGetterGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeInstanceGetterGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeInstanceGetterGen();
    friend ::djinni::JniClass<NativeInstanceGetterGen>;
    friend ::djinni::JniInterface<::gearsbox::InstanceGetterGen, NativeInstanceGetterGen>;

};

}  // namespace djinni_generated
