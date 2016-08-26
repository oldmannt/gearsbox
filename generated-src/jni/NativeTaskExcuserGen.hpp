// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include "djinni_support.hpp"
#include "task_excuser_gen.hpp"

namespace djinni_generated {

class NativeTaskExcuserGen final : ::djinni::JniInterface<::gearsbox::TaskExcuserGen, NativeTaskExcuserGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::TaskExcuserGen>;
    using CppOptType = std::shared_ptr<::gearsbox::TaskExcuserGen>;
    using JniType = jobject;

    using Boxed = NativeTaskExcuserGen;

    ~NativeTaskExcuserGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeTaskExcuserGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeTaskExcuserGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeTaskExcuserGen();
    friend ::djinni::JniClass<NativeTaskExcuserGen>;
    friend ::djinni::JniInterface<::gearsbox::TaskExcuserGen, NativeTaskExcuserGen>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::TaskExcuserGen
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        void excuse(const std::shared_ptr<::gearsbox::TaskInfoGen> & info) override;

    private:
        friend ::djinni::JniInterface<::gearsbox::TaskExcuserGen, ::djinni_generated::NativeTaskExcuserGen>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/TaskExcuserGen") };
    const jmethodID method_excuse { ::djinni::jniGetMethodID(clazz.get(), "excuse", "(Ldyno/fun/gearsbox/TaskInfoGen;)V") };
};

}  // namespace djinni_generated
