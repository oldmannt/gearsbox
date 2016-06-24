// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include "djinni_support.hpp"
#include "view_gen.hpp"

namespace djinni_generated {

class NativeViewGen final : ::djinni::JniInterface<::gearsbox::ViewGen, NativeViewGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::ViewGen>;
    using CppOptType = std::shared_ptr<::gearsbox::ViewGen>;
    using JniType = jobject;

    using Boxed = NativeViewGen;

    ~NativeViewGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeViewGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeViewGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeViewGen();
    friend ::djinni::JniClass<NativeViewGen>;
    friend ::djinni::JniInterface<::gearsbox::ViewGen, NativeViewGen>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::ViewGen
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        std::string getId() override;
        void setFrame(const ::gearsbox::ViewFrame & frame) override;
        ::gearsbox::ViewFrame getFrame() override;
        void setBackgroundColor(float a, float r, float g, float b) override;
        void setVisiable(bool v) override;
        ::gearsbox::ViewType getType() override;
        void setBoardColor(const ::gearsbox::ArgbColor & color) override;
        void setBoardWidth(float width) override;
        void setText(const std::string & text) override;
        void setTextColor(const ::gearsbox::ArgbColor & color) override;
        void setFontSize(int32_t size) override;
        std::shared_ptr<::gearsbox::ViewGen> getSubView(const std::string & id) override;
        std::shared_ptr<::gearsbox::ViewGen> addSubViewById(const std::string & id, ::gearsbox::ViewType type) override;
        std::shared_ptr<::gearsbox::ViewGen> addSubView(const ::gearsbox::ViewConf & conf) override;
        bool removeSubView(const std::string & id) override;
        void removeAllSubView() override;
        void addConstraint(const ::gearsbox::ViewConstraint & constraint) override;
        void setEventHandler(const std::shared_ptr<::gearsbox::ViewEventHandler> & handler) override;

    private:
        friend ::djinni::JniInterface<::gearsbox::ViewGen, ::djinni_generated::NativeViewGen>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/ViewGen") };
    const jmethodID method_getId { ::djinni::jniGetMethodID(clazz.get(), "getId", "()Ljava/lang/String;") };
    const jmethodID method_setFrame { ::djinni::jniGetMethodID(clazz.get(), "setFrame", "(Ldyno/fun/gearsbox/ViewFrame;)V") };
    const jmethodID method_getFrame { ::djinni::jniGetMethodID(clazz.get(), "getFrame", "()Ldyno/fun/gearsbox/ViewFrame;") };
    const jmethodID method_setBackgroundColor { ::djinni::jniGetMethodID(clazz.get(), "setBackgroundColor", "(FFFF)V") };
    const jmethodID method_setVisiable { ::djinni::jniGetMethodID(clazz.get(), "setVisiable", "(Z)V") };
    const jmethodID method_getType { ::djinni::jniGetMethodID(clazz.get(), "getType", "()Ldyno/fun/gearsbox/ViewType;") };
    const jmethodID method_setBoardColor { ::djinni::jniGetMethodID(clazz.get(), "setBoardColor", "(Ldyno/fun/gearsbox/ArgbColor;)V") };
    const jmethodID method_setBoardWidth { ::djinni::jniGetMethodID(clazz.get(), "setBoardWidth", "(F)V") };
    const jmethodID method_setText { ::djinni::jniGetMethodID(clazz.get(), "setText", "(Ljava/lang/String;)V") };
    const jmethodID method_setTextColor { ::djinni::jniGetMethodID(clazz.get(), "setTextColor", "(Ldyno/fun/gearsbox/ArgbColor;)V") };
    const jmethodID method_setFontSize { ::djinni::jniGetMethodID(clazz.get(), "setFontSize", "(I)V") };
    const jmethodID method_getSubView { ::djinni::jniGetMethodID(clazz.get(), "getSubView", "(Ljava/lang/String;)Ldyno/fun/gearsbox/ViewGen;") };
    const jmethodID method_addSubViewById { ::djinni::jniGetMethodID(clazz.get(), "addSubViewById", "(Ljava/lang/String;Ldyno/fun/gearsbox/ViewType;)Ldyno/fun/gearsbox/ViewGen;") };
    const jmethodID method_addSubView { ::djinni::jniGetMethodID(clazz.get(), "addSubView", "(Ldyno/fun/gearsbox/ViewConf;)Ldyno/fun/gearsbox/ViewGen;") };
    const jmethodID method_removeSubView { ::djinni::jniGetMethodID(clazz.get(), "removeSubView", "(Ljava/lang/String;)Z") };
    const jmethodID method_removeAllSubView { ::djinni::jniGetMethodID(clazz.get(), "removeAllSubView", "()V") };
    const jmethodID method_addConstraint { ::djinni::jniGetMethodID(clazz.get(), "addConstraint", "(Ldyno/fun/gearsbox/ViewConstraint;)V") };
    const jmethodID method_setEventHandler { ::djinni::jniGetMethodID(clazz.get(), "setEventHandler", "(Ldyno/fun/gearsbox/ViewEventHandler;)V") };
};

}  // namespace djinni_generated
