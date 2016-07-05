#pragma once


#include "view_conf_base.hpp"
#include "argb_color.hpp"
#include "text_keyboard.hpp"

namespace gearsbox {
    
    struct ViewConf : public ViewConfBase
    {
        using ViewConfBase::ViewConfBase;
        
        ViewConf():ViewConfBase(""                     // std::string id_,
                                          , ViewType::BASE       // ViewType type_,
                                          , ViewFrame(0,0,0,0)   // ViewFrame frame_,
                                          , ArgbColor(0,0,0,0)   // ArgbColor bgcolor_,
                                          , -1                   // int32_t fontsize_,
                                          , TextAlign::NONE      // TextAlign textalign_,
                                          , TextBoarder::NONE    // TextBoarder textboarder_,
                                          , ""                   // std::string text_,
                                          , false                // numericText
                                          , TextKeyboard::DEFAULT// keyboardtype
                                          , -1                  // maxlongth
                                          , std::vector<ViewConstraint>()
                                          , std::vector<ViewConf>()){}
    };
}