// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include "djinni_support.hpp"
#include "video_writer_result_handler.hpp"

namespace djinni_generated {

class NativeVideoWriterResultHandler final : ::djinni::JniInterface<::gearsbox::VideoWriterResultHandler, NativeVideoWriterResultHandler> {
public:
    using CppType = std::shared_ptr<::gearsbox::VideoWriterResultHandler>;
    using CppOptType = std::shared_ptr<::gearsbox::VideoWriterResultHandler>;
    using JniType = jobject;

    using Boxed = NativeVideoWriterResultHandler;

    ~NativeVideoWriterResultHandler();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeVideoWriterResultHandler>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeVideoWriterResultHandler>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeVideoWriterResultHandler();
    friend ::djinni::JniClass<NativeVideoWriterResultHandler>;
    friend ::djinni::JniInterface<::gearsbox::VideoWriterResultHandler, NativeVideoWriterResultHandler>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::VideoWriterResultHandler
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        void onComplete(bool success, const std::string & path, int32_t duration) override;
        void beforeComplete() override;
        void onProgress(float percent) override;

    private:
        friend ::djinni::JniInterface<::gearsbox::VideoWriterResultHandler, ::djinni_generated::NativeVideoWriterResultHandler>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/VideoWriterResultHandler") };
    const jmethodID method_onComplete { ::djinni::jniGetMethodID(clazz.get(), "onComplete", "(ZLjava/lang/String;I)V") };
    const jmethodID method_beforeComplete { ::djinni::jniGetMethodID(clazz.get(), "beforeComplete", "()V") };
    const jmethodID method_onProgress { ::djinni::jniGetMethodID(clazz.get(), "onProgress", "(F)V") };
};

}  // namespace djinni_generated
