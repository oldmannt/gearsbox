// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include "djinni_support.hpp"
#include "platform_utility_gen.hpp"

namespace djinni_generated {

class NativePlatformUtilityGen final : ::djinni::JniInterface<::gearsbox::PlatformUtilityGen, NativePlatformUtilityGen> {
public:
    using CppType = std::shared_ptr<::gearsbox::PlatformUtilityGen>;
    using CppOptType = std::shared_ptr<::gearsbox::PlatformUtilityGen>;
    using JniType = jobject;

    using Boxed = NativePlatformUtilityGen;

    ~NativePlatformUtilityGen();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativePlatformUtilityGen>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativePlatformUtilityGen>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativePlatformUtilityGen();
    friend ::djinni::JniClass<NativePlatformUtilityGen>;
    friend ::djinni::JniInterface<::gearsbox::PlatformUtilityGen, NativePlatformUtilityGen>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::gearsbox::PlatformUtilityGen
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        int64_t getSystemTickNano() override;
        int64_t getSystemTickMsec() override;
        double getSystemTickSec() override;
        void endEniting(bool force) override;
        ::gearsbox::LangType getLanguage() override;
        std::string getHomeDirectory() override;
        std::string getPackFilePath(const std::string & file) override;
        std::string getPackFileBuffer(const std::string & file) override;
        std::string getPackFileToHomePath(const std::string & file) override;
        std::unordered_set<std::string> getFilesFromPathBySuffix(const std::string & path, const std::string & suffix) override;
        std::string getSubDirInHome(const std::string & sub_dir) override;
        std::string getFileNameFromPath(const std::string & path) override;
        std::shared_ptr<::gearsbox::FileInfoGen> getFileInfo(const std::string & path_name) override;
        bool deleteFile(const std::string & fullpath) override;
        bool isVideoFileCompatibleToSavedPhotosAlbum(const std::string & fullpath) override;
        bool saveVideoFileToSavedPhotosAlbum(const std::string & fullpath) override;
        void playVideo(const std::string & file) override;
        std::shared_ptr<::gearsbox::VideoFrameGen> createVideoFrame() override;

    private:
        friend ::djinni::JniInterface<::gearsbox::PlatformUtilityGen, ::djinni_generated::NativePlatformUtilityGen>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/PlatformUtilityGen") };
    const jmethodID method_getSystemTickNano { ::djinni::jniGetMethodID(clazz.get(), "getSystemTickNano", "()J") };
    const jmethodID method_getSystemTickMsec { ::djinni::jniGetMethodID(clazz.get(), "getSystemTickMsec", "()J") };
    const jmethodID method_getSystemTickSec { ::djinni::jniGetMethodID(clazz.get(), "getSystemTickSec", "()D") };
    const jmethodID method_endEniting { ::djinni::jniGetMethodID(clazz.get(), "endEniting", "(Z)V") };
    const jmethodID method_getLanguage { ::djinni::jniGetMethodID(clazz.get(), "getLanguage", "()Ldyno/fun/gearsbox/LangType;") };
    const jmethodID method_getHomeDirectory { ::djinni::jniGetMethodID(clazz.get(), "getHomeDirectory", "()Ljava/lang/String;") };
    const jmethodID method_getPackFilePath { ::djinni::jniGetMethodID(clazz.get(), "getPackFilePath", "(Ljava/lang/String;)Ljava/lang/String;") };
    const jmethodID method_getPackFileBuffer { ::djinni::jniGetMethodID(clazz.get(), "getPackFileBuffer", "(Ljava/lang/String;)Ljava/lang/String;") };
    const jmethodID method_getPackFileToHomePath { ::djinni::jniGetMethodID(clazz.get(), "getPackFileToHomePath", "(Ljava/lang/String;)Ljava/lang/String;") };
    const jmethodID method_getFilesFromPathBySuffix { ::djinni::jniGetMethodID(clazz.get(), "getFilesFromPathBySuffix", "(Ljava/lang/String;Ljava/lang/String;)Ljava/util/HashSet;") };
    const jmethodID method_getSubDirInHome { ::djinni::jniGetMethodID(clazz.get(), "getSubDirInHome", "(Ljava/lang/String;)Ljava/lang/String;") };
    const jmethodID method_getFileNameFromPath { ::djinni::jniGetMethodID(clazz.get(), "getFileNameFromPath", "(Ljava/lang/String;)Ljava/lang/String;") };
    const jmethodID method_getFileInfo { ::djinni::jniGetMethodID(clazz.get(), "getFileInfo", "(Ljava/lang/String;)Ldyno/fun/gearsbox/FileInfoGen;") };
    const jmethodID method_deleteFile { ::djinni::jniGetMethodID(clazz.get(), "deleteFile", "(Ljava/lang/String;)Z") };
    const jmethodID method_isVideoFileCompatibleToSavedPhotosAlbum { ::djinni::jniGetMethodID(clazz.get(), "isVideoFileCompatibleToSavedPhotosAlbum", "(Ljava/lang/String;)Z") };
    const jmethodID method_saveVideoFileToSavedPhotosAlbum { ::djinni::jniGetMethodID(clazz.get(), "saveVideoFileToSavedPhotosAlbum", "(Ljava/lang/String;)Z") };
    const jmethodID method_playVideo { ::djinni::jniGetMethodID(clazz.get(), "playVideo", "(Ljava/lang/String;)V") };
    const jmethodID method_createVideoFrame { ::djinni::jniGetMethodID(clazz.get(), "createVideoFrame", "()Ldyno/fun/gearsbox/VideoFrameGen;") };
};

}  // namespace djinni_generated
