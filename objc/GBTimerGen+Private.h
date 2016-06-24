// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "timer_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class GBTimerGen;

namespace djinni_generated {

class TimerGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::TimerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::TimerGen>;
    using ObjcType = GBTimerGen*;

    using Boxed = TimerGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated

