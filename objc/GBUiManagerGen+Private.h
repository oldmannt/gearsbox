// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "ui_manager_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class GBUiManagerGen;

namespace djinni_generated {

class UiManagerGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::UiManagerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::UiManagerGen>;
    using ObjcType = GBUiManagerGen*;

    using Boxed = UiManagerGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated

