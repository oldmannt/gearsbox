//
//  ui_vaule_checker_imp.cpp
//  gearsbox
//
//  Created by dyno on 6/6/16.
//
//
#include "argb_color.hpp"
#include "ui_value_checker_imp.hpp"

#include "view_frame.hpp"
#include "text_boarder.hpp"

using namespace gearsbox;

std::shared_ptr<UiValueCheckerGen> UiValueCheckerGen::instance(){
    static std::shared_ptr<UiValueCheckerGen> s_ptr = std::make_shared<UivalueCheckerImp>();
    return s_ptr;
}
