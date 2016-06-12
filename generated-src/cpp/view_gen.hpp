// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <memory>
#include <string>

namespace gearsbox {

class ViewEventHandler;
enum class ViewType;
struct ArgbColor;
struct ViewConf;
struct ViewConstraint;
struct ViewFrame;

class ViewGen {
public:
    virtual ~ViewGen() {}

    virtual std::string getId() = 0;

    virtual void setFrame(const ViewFrame & frame) = 0;

    virtual ViewFrame getFrame() = 0;

    virtual void setBackgroundColor(float a, float r, float g, float b) = 0;

    virtual void setVisiable(bool v) = 0;

    virtual ViewType getType() = 0;

    virtual void setBoardColor(const ArgbColor & color) = 0;

    virtual void setBoardWidth(float width) = 0;

    virtual void setText(const std::string & text) = 0;

    virtual std::shared_ptr<ViewGen> getSubView(const std::string & id) = 0;

    virtual std::shared_ptr<ViewGen> addSubViewById(const std::string & id, ViewType type) = 0;

    virtual std::shared_ptr<ViewGen> addSubView(const ViewConf & conf) = 0;

    virtual bool removeSubView(const std::string & id) = 0;

    virtual void removeAllSubView() = 0;

    virtual void addConstraint(const ViewConstraint & constraint) = 0;

    virtual void setEventHandler(const std::shared_ptr<ViewEventHandler> & handler) = 0;
};

}  // namespace gearsbox
