//
//  ui_value_checker_imp.hpp
//  gearsbox
//
//  Created by dyno on 6/6/16.
//
//

#ifndef ui_value_checker_imp_h
#define ui_value_checker_imp_h

#include "ui_value_checker_gen.hpp"
#include "argb_color.hpp"
#include "view_frame.hpp"
#include "text_boarder.hpp"
#include "text_align.hpp"
#include <math.h>

namespace gearsbox{
    
class UivalueCheckerImp: public UiValueCheckerGen {
public:
    virtual ~UivalueCheckerImp() {}
    
    virtual bool isValidColor(const ArgbColor & value){
        return (value.a > 0.000001f ||
                value.r > 0.000001f ||
                value.g > 0.000001f ||
                value.b > 0.000001f);
    };
    
    virtual bool isValidFrame(const ViewFrame & value){
        return (fabsf(value.x-0.0f) > 0.000001f ||
                fabsf(value.y-0.0f) > 0.000001f ||
                fabsf(value.w-0.0f) > 0.000001f ||
                fabsf(value.h-0.0f) > 0.000001f);
    }
    
    virtual bool isValidTextBoarder(TextBoarder value){
        return (value != TextBoarder::NONE);
    }
    
    virtual bool isValidTextAlign(TextAlign value){
        return (value != TextAlign::NONE);
    }
};
    
}


#endif /* ui_value_checker_imp_h */
