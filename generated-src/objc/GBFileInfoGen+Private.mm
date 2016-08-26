// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBFileInfoGen+Private.h"
#import "GBFileInfoGen.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class FileInfoGen::ObjcProxy final
: public ::gearsbox::FileInfoGen
, public ::djinni::ObjcProxyCache::Handle<ObjcType>
{
public:
    using Handle::Handle;
    bool initialize(const std::string & c_path) override
    {
        @autoreleasepool {
            auto r = [Handle::get() initialize:(::djinni::String::fromCpp(c_path))];
            return ::djinni::Bool::toCpp(r);
        }
    }
    int64_t getSize() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getSize];
            return ::djinni::I64::toCpp(r);
        }
    }
    std::chrono::system_clock::time_point getCreateDate() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getCreateDate];
            return ::djinni::Date::toCpp(r);
        }
    }
    std::string getName() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getName];
            return ::djinni::String::toCpp(r);
        }
    }
    std::string getSuffix() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getSuffix];
            return ::djinni::String::toCpp(r);
        }
    }
    std::string getPrefix() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getPrefix];
            return ::djinni::String::toCpp(r);
        }
    }
    std::string getPath() override
    {
        @autoreleasepool {
            auto r = [Handle::get() getPath];
            return ::djinni::String::toCpp(r);
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto FileInfoGen::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto FileInfoGen::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return dynamic_cast<ObjcProxy&>(*cpp).Handle::get();
}

}  // namespace djinni_generated
