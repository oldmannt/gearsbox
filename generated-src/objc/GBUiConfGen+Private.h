// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "ui_conf_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class GBUiConfGen;

namespace djinni_generated {

class UiConfGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::UiConfGen>;
    using CppOptType = std::shared_ptr<::gearsbox::UiConfGen>;
    using ObjcType = GBUiConfGen*;

    using Boxed = UiConfGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated

