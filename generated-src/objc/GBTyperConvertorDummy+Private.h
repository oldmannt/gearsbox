// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#include "typer_convertor_dummy.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol GBTyperConvertorDummy;

namespace djinni_generated {

class TyperConvertorDummy
{
public:
    using CppType = std::shared_ptr<::gearsbox::TyperConvertorDummy>;
    using CppOptType = std::shared_ptr<::gearsbox::TyperConvertorDummy>;
    using ObjcType = id<GBTyperConvertorDummy>;

    using Boxed = TyperConvertorDummy;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
