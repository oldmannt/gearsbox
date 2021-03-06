// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#pragma once

#include "djinni_support.hpp"
#include "video_orientation.hpp"

namespace djinni_generated {

class NativeVideoOrientation final : ::djinni::JniEnum {
public:
    using CppType = ::gearsbox::VideoOrientation;
    using JniType = jobject;

    using Boxed = NativeVideoOrientation;

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return static_cast<CppType>(::djinni::JniClass<NativeVideoOrientation>::get().ordinal(jniEnv, j)); }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, CppType c) { return ::djinni::JniClass<NativeVideoOrientation>::get().create(jniEnv, static_cast<jint>(c)); }

private:
    NativeVideoOrientation() : JniEnum("dyno/fun/gearsbox/VideoOrientation") {}
    friend ::djinni::JniClass<NativeVideoOrientation>;
};

}  // namespace djinni_generated
