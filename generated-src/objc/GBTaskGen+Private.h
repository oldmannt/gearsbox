// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "task_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol GBTaskGen;

namespace djinni_generated {

class TaskGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::TaskGen>;
    using CppOptType = std::shared_ptr<::gearsbox::TaskGen>;
    using ObjcType = id<GBTaskGen>;

    using Boxed = TaskGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
