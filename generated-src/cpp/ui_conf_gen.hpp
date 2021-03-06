// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once
#include "view_conf.hpp"
#include <memory>
#include <string>
#include <vector>

namespace gearsbox {

struct ViewConstraint;

class UiConfGen {
public:
virtual ~UiConfGen() {}

static std::shared_ptr<UiConfGen> instance();

virtual bool initialize(const std::string & cfg) = 0;

virtual bool load(const std::string & cfg) = 0;

virtual std::vector<ViewConstraint> getConstraints(const std::string & name) const = 0;

virtual ViewConf getViewConf(const std::string & nmae) const = 0;
};

}  // namespace gearsbox
