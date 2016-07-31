// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include "camera_controller_gen.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeCameraControllerGen final : ::djinni::JniInterface<::gearsbox::CameraControllerGen, NativeCameraControllerGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::CameraControllerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::CameraControllerGen>;
    using JniType = jobject;

    using Boxed = NativeCameraControllerGen;

    ~NativeCameraControllerGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeCameraControllerGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeCameraControllerGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeCameraControllerGen();
    friend ::djinni::JniClass<NativeCameraControllerGen>;
    friend ::djinni::JniInterface<::gearsbox::CameraControllerGen, NativeCameraControllerGen>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::CameraControllerGen
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        void startCamera() override;
        void stopCamera() override;
        void setFlash(::gearsbox::CameraFlash mode) override;
        void setQuality(::gearsbox::CameraQuality quality) override;
        void switchFront(bool front) override;
        bool isFront() override;
        ::gearsbox::CameraFlash getFlash() override;
        ::gearsbox::CameraQuality getQuality() override;
        void setFousePoint(int32_t x, int32_t y) override;
        void setExposurePoint(int32_t x, int32_t y) override;
        void setZoom(float zoom) override;
        float getZoom() override;
        void setISO(int32_t iso) override;
        int32_t getISO() override;
        void setShutter(int32_t shutter) override;
        int32_t getShutter() override;
        void setAperture(float f) override;
        float getAperture() override;
        std::shared_ptr<::gearsbox::VideoFrameGen> captureOneFrame() override;

    private:
        friend ::djinni::JniInterface<::gearsbox::CameraControllerGen, ::djinni_generated::NativeCameraControllerGen>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/CameraControllerGen") };
    const jmethodID method_startCamera { ::djinni::jniGetMethodID(clazz.get(), "startCamera", "()V") };
    const jmethodID method_stopCamera { ::djinni::jniGetMethodID(clazz.get(), "stopCamera", "()V") };
    const jmethodID method_setFlash { ::djinni::jniGetMethodID(clazz.get(), "setFlash", "(Ldyno/fun/gearsbox/CameraFlash;)V") };
    const jmethodID method_setQuality { ::djinni::jniGetMethodID(clazz.get(), "setQuality", "(Ldyno/fun/gearsbox/CameraQuality;)V") };
    const jmethodID method_switchFront { ::djinni::jniGetMethodID(clazz.get(), "switchFront", "(Z)V") };
    const jmethodID method_isFront { ::djinni::jniGetMethodID(clazz.get(), "isFront", "()Z") };
    const jmethodID method_getFlash { ::djinni::jniGetMethodID(clazz.get(), "getFlash", "()Ldyno/fun/gearsbox/CameraFlash;") };
    const jmethodID method_getQuality { ::djinni::jniGetMethodID(clazz.get(), "getQuality", "()Ldyno/fun/gearsbox/CameraQuality;") };
    const jmethodID method_setFousePoint { ::djinni::jniGetMethodID(clazz.get(), "setFousePoint", "(II)V") };
    const jmethodID method_setExposurePoint { ::djinni::jniGetMethodID(clazz.get(), "setExposurePoint", "(II)V") };
    const jmethodID method_setZoom { ::djinni::jniGetMethodID(clazz.get(), "setZoom", "(F)V") };
    const jmethodID method_getZoom { ::djinni::jniGetMethodID(clazz.get(), "getZoom", "()F") };
    const jmethodID method_setISO { ::djinni::jniGetMethodID(clazz.get(), "setISO", "(I)V") };
    const jmethodID method_getISO { ::djinni::jniGetMethodID(clazz.get(), "getISO", "()I") };
    const jmethodID method_setShutter { ::djinni::jniGetMethodID(clazz.get(), "setShutter", "(I)V") };
    const jmethodID method_getShutter { ::djinni::jniGetMethodID(clazz.get(), "getShutter", "()I") };
    const jmethodID method_setAperture { ::djinni::jniGetMethodID(clazz.get(), "setAperture", "(F)V") };
    const jmethodID method_getAperture { ::djinni::jniGetMethodID(clazz.get(), "getAperture", "()F") };
    const jmethodID method_captureOneFrame { ::djinni::jniGetMethodID(clazz.get(), "captureOneFrame", "()Ldyno/fun/gearsbox/VideoFrameGen;") };
};

}  // namespace djinni_generated