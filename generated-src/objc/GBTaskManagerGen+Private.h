// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#include "task_manager_gen.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class GBTaskManagerGen;

namespace djinni_generated {

class TaskManagerGen
{
public:
    using CppType = std::shared_ptr<::gearsbox::TaskManagerGen>;
    using CppOptType = std::shared_ptr<::gearsbox::TaskManagerGen>;
    using ObjcType = GBTaskManagerGen*;

    using Boxed = TaskManagerGen;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
