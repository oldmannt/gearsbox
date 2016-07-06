// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include "crash_handler_gen.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeCrashHandlerGen final : ::djinni::JniInterface<::gearsbox::CrashHandlerGen, NativeCrashHandlerGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::CrashHandlerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::CrashHandlerGen>;
    using JniType = jobject;

    using Boxed = NativeCrashHandlerGen;

    ~NativeCrashHandlerGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeCrashHandlerGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeCrashHandlerGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeCrashHandlerGen();
    friend ::djinni::JniClass<NativeCrashHandlerGen>;
    friend ::djinni::JniInterface<::gearsbox::CrashHandlerGen, NativeCrashHandlerGen>;

};

}  // namespace djinni_generated