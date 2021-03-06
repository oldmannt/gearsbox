// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#pragma once

#include "argb_color.hpp"
#include "text_align.hpp"
#include "text_boarder.hpp"
#include "text_keyboard.hpp"
#include "view_constraint.hpp"
#include "view_frame.hpp"
#include "view_type.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace gearsbox {

struct ViewConf; // Requiring extended class

struct ViewConfBase {

    static ViewFrame const NOFRAME;

    static ArgbColor const NOGBCOLOR;
    std::string id;
    ViewType type;
    ViewFrame frame;
    ArgbColor bgcolor;
    int32_t fontsize;
    TextAlign textalign;
    TextBoarder textboarder;
    std::string text;
    bool numericText;
    TextKeyboard keyboardtype;
    int32_t maxlength;
    std::vector<ViewConstraint> constraints;
    std::vector<ViewConf> subviews;

    ViewConfBase(std::string id_,
                 ViewType type_,
                 ViewFrame frame_,
                 ArgbColor bgcolor_,
                 int32_t fontsize_,
                 TextAlign textalign_,
                 TextBoarder textboarder_,
                 std::string text_,
                 bool numericText_,
                 TextKeyboard keyboardtype_,
                 int32_t maxlength_,
                 std::vector<ViewConstraint> constraints_,
                 std::vector<ViewConf> subviews_)
    : id(std::move(id_))
    , type(std::move(type_))
    , frame(std::move(frame_))
    , bgcolor(std::move(bgcolor_))
    , fontsize(std::move(fontsize_))
    , textalign(std::move(textalign_))
    , textboarder(std::move(textboarder_))
    , text(std::move(text_))
    , numericText(std::move(numericText_))
    , keyboardtype(std::move(keyboardtype_))
    , maxlength(std::move(maxlength_))
    , constraints(std::move(constraints_))
    , subviews(std::move(subviews_))
    {}

    virtual ~ViewConfBase() = default;

protected:
    ViewConfBase(const ViewConfBase&) = default;
    ViewConfBase(ViewConfBase&&) = default;
    ViewConfBase& operator=(const ViewConfBase&) = default;
    ViewConfBase& operator=(ViewConfBase&&) = default;
};

}  // namespace gearsbox
