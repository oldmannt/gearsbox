// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include "djinni_support.hpp"
#include "video_frame_gen.hpp"

namespace djinni_generated {

class NativeVideoFrameGen final : ::djinni::JniInterface<::gearsbox::VideoFrameGen, NativeVideoFrameGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::VideoFrameGen>;
    using CppOptType = std::shared_ptr<::gearsbox::VideoFrameGen>;
    using JniType = jobject;

    using Boxed = NativeVideoFrameGen;

    ~NativeVideoFrameGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeVideoFrameGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeVideoFrameGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeVideoFrameGen();
    friend ::djinni::JniClass<NativeVideoFrameGen>;
    friend ::djinni::JniInterface<::gearsbox::VideoFrameGen, NativeVideoFrameGen>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::VideoFrameGen
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        int64_t getData() override;
        int32_t getWidth() override;
        int32_t getHeight() override;
        int64_t getSize() override;

    private:
        friend ::djinni::JniInterface<::gearsbox::VideoFrameGen, ::djinni_generated::NativeVideoFrameGen>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/VideoFrameGen") };
    const jmethodID method_getData { ::djinni::jniGetMethodID(clazz.get(), "getData", "()J") };
    const jmethodID method_getWidth { ::djinni::jniGetMethodID(clazz.get(), "getWidth", "()I") };
    const jmethodID method_getHeight { ::djinni::jniGetMethodID(clazz.get(), "getHeight", "()I") };
    const jmethodID method_getSize { ::djinni::jniGetMethodID(clazz.get(), "getSize", "()J") };
};

}  // namespace djinni_generated