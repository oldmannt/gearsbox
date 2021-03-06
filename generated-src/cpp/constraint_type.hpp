// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <functional>

namespace gearsbox {

enum class ConstraintType : int {
    NONE,
    LEADING,
    TRAILING,
    TOP,
    BOTTOM,
    WIDTH,
    HEIGHT,
    CENTERX,
    CENTERY,
};

}  // namespace gearsbox

namespace std {

template <>
struct hash<::gearsbox::ConstraintType> {
    size_t operator()(::gearsbox::ConstraintType type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

}  // namespace std
