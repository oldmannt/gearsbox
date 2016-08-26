// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <memory>
#include <string>

namespace gearsbox {

class ViewGen;
enum class ViewType;
struct ViewConf;

class ViewFactoryGen {
public:
    virtual ~ViewFactoryGen() {}

    virtual std::shared_ptr<ViewGen> createView(const ViewConf & conf) = 0;

    virtual std::shared_ptr<ViewGen> createViewById(const std::string & id, ViewType type) = 0;

    virtual bool injectView(const std::shared_ptr<ViewGen> & view) = 0;

    virtual void showViewController(const std::string & id, bool animated) = 0;
};

}  // namespace gearsbox
