// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include "djinni_support.hpp"
#include "task_info.hpp"

namespace djinni_generated {

class NativeTaskInfo final {
public:
    using CppType = ::gearsbox::TaskInfo;
    using JniType = jobject;

    using Boxed = NativeTaskInfo;

    ~NativeTaskInfo();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    NativeTaskInfo();
    friend ::djinni::JniClass<NativeTaskInfo>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("dyno/fun/gearsbox/TaskInfo") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(JZ)V") };
    const jfieldID field_mDelay { ::djinni::jniGetFieldID(clazz.get(), "mDelay", "J") };
    const jfieldID field_mRepeate { ::djinni::jniGetFieldID(clazz.get(), "mRepeate", "Z") };
};

}  // namespace djinni_generated