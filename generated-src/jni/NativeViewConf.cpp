// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "NativeViewConf.hpp"  // my header
#include "Marshal.hpp"
#include "NativeArgbColor.hpp"
#include "NativeTextAlign.hpp"
#include "NativeTextBoarder.hpp"
#include "NativeTextKeyboard.hpp"
#include "NativeViewConf.hpp"
#include "NativeViewConstraint.hpp"
#include "NativeViewFrame.hpp"
#include "NativeViewType.hpp"

namespace djinni_generated {

NativeViewConf::NativeViewConf() = default;

NativeViewConf::~NativeViewConf() = default;

auto NativeViewConf::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<NativeViewConf>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c.id)),
                                                           ::djinni::get(::djinni_generated::NativeViewType::fromCpp(jniEnv, c.type)),
                                                           ::djinni::get(::djinni_generated::NativeViewFrame::fromCpp(jniEnv, c.frame)),
                                                           ::djinni::get(::djinni_generated::NativeArgbColor::fromCpp(jniEnv, c.bgcolor)),
                                                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c.fontsize)),
                                                           ::djinni::get(::djinni_generated::NativeTextAlign::fromCpp(jniEnv, c.textalign)),
                                                           ::djinni::get(::djinni_generated::NativeTextBoarder::fromCpp(jniEnv, c.textboarder)),
                                                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c.text)),
                                                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c.numericText)),
                                                           ::djinni::get(::djinni_generated::NativeTextKeyboard::fromCpp(jniEnv, c.keyboardtype)),
                                                           ::djinni::get(::djinni::List<::djinni_generated::NativeViewConstraint>::fromCpp(jniEnv, c.constraints)),
                                                           ::djinni::get(::djinni::Map<::djinni::String, ::djinni_generated::NativeViewConf>::fromCpp(jniEnv, c.subviews)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto NativeViewConf::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 13);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<NativeViewConf>::get();
    return {::djinni::String::toCpp(jniEnv, (jstring)jniEnv->GetObjectField(j, data.field_mId)),
            ::djinni_generated::NativeViewType::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mType)),
            ::djinni_generated::NativeViewFrame::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mFrame)),
            ::djinni_generated::NativeArgbColor::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mBgcolor)),
            ::djinni::I32::toCpp(jniEnv, jniEnv->GetIntField(j, data.field_mFontsize)),
            ::djinni_generated::NativeTextAlign::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mTextalign)),
            ::djinni_generated::NativeTextBoarder::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mTextboarder)),
            ::djinni::String::toCpp(jniEnv, (jstring)jniEnv->GetObjectField(j, data.field_mText)),
            ::djinni::Bool::toCpp(jniEnv, jniEnv->GetBooleanField(j, data.field_mNumericText)),
            ::djinni_generated::NativeTextKeyboard::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mKeyboardtype)),
            ::djinni::List<::djinni_generated::NativeViewConstraint>::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mConstraints)),
            ::djinni::Map<::djinni::String, ::djinni_generated::NativeViewConf>::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mSubviews))};
}

}  // namespace djinni_generated
