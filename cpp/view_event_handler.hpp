// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <memory>

namespace gearsbox {

class ViewGen;
struct ViewEventParam;

class ViewEventHandler {
public:
    virtual ~ViewEventHandler() {}

    virtual bool handle(const ViewEventParam & param, const std::shared_ptr<ViewGen> & view) = 0;
};

}  // namespace gearsbox
