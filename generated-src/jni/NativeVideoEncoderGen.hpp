// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include "djinni_support.hpp"
#include "video_encoder_gen.hpp"

namespace djinni_generated {

class NativeVideoEncoderGen final : ::djinni::JniInterface<::gearsbox::VideoEncoderGen, NativeVideoEncoderGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::VideoEncoderGen>;
    using CppOptType = std::shared_ptr<::gearsbox::VideoEncoderGen>;
    using JniType = jobject;

    using Boxed = NativeVideoEncoderGen;

    ~NativeVideoEncoderGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeVideoEncoderGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeVideoEncoderGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeVideoEncoderGen();
    friend ::djinni::JniClass<NativeVideoEncoderGen>;
    friend ::djinni::JniInterface<::gearsbox::VideoEncoderGen, NativeVideoEncoderGen>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::VideoEncoderGen
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        bool initialize(const std::string & filepath, int32_t fps, int32_t bitrate, int32_t width, int32_t height) override;
        void encodeFrame(const std::shared_ptr<::gearsbox::VideoFrameGen> & frame) override;
        void saveNRelease() override;

    private:
        friend ::djinni::JniInterface<::gearsbox::VideoEncoderGen, ::djinni_generated::NativeVideoEncoderGen>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/VideoEncoderGen") };
    const jmethodID method_initialize { ::djinni::jniGetMethodID(clazz.get(), "initialize", "(Ljava/lang/String;IIII)Z") };
    const jmethodID method_encodeFrame { ::djinni::jniGetMethodID(clazz.get(), "encodeFrame", "(Ldyno/fun/gearsbox/VideoFrameGen;)V") };
    const jmethodID method_saveNRelease { ::djinni::jniGetMethodID(clazz.get(), "saveNRelease", "()V") };
};

}  // namespace djinni_generated
