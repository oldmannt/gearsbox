// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <functional>

namespace gearsbox {

enum class TextBoarder : int {
    NONE,
    LINE,
    BEZEL,
    ROUNDEDRECT,
};

}  // namespace gearsbox

namespace std {

template <>
struct hash<::gearsbox::TextBoarder> {
    size_t operator()(::gearsbox::TextBoarder type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

}  // namespace std