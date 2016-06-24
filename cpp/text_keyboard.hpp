// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include <functional>

namespace gearsbox {

enum class TextKeyboard : int {
    DEFAULT,
    ASCII,
    URL,
    NUMBERPAD,
    PHONEPAD,
    DECIMALPAD,
};

}  // namespace gearsbox

namespace std {

template <>
struct hash<::gearsbox::TextKeyboard> {
    size_t operator()(::gearsbox::TextKeyboard type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

}  // namespace std
