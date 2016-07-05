//
//  utils.cpp
//  gearsbox
//
//  Created by dyno on 6/23/16.
//
//

#include <fstream>

#include "ilog.h"
#include "utils.hpp"

using namespace gearsbox;

bool gearsbox::readJson(const std::string& param, Json::Value& config){
    Json::Reader reader;
    if (std::string::npos != param.find(".json")){
        std::ifstream ifs(param);
        if (!ifs.is_open()){
            G_LOG_FC(LOG_ERROR, "open file failed %s", param.c_str());
            return false;
        }
        
        if (!reader.parse(ifs, config)){
            std::string err = reader.getFormatedErrorMessages();
            G_LOG_FC(LOG_ERROR, "read err:%s file:%s", err.c_str(), param.c_str());
            return false;
        }
    }else if (!reader.parse(param, config)){
        std::string err = reader.getFormatedErrorMessages();
        G_LOG_FC(LOG_ERROR, "read err:%s param:%s", err.c_str(), param.c_str());
        return false;
    }
    
    return true;
}
/*
ViewConf gearsbox::emptyViewConf(){
    return std::move(ViewConf(""                     // std::string id_,
                                      , ViewType::BASE       // ViewType type_,
                                      , ViewFrame(0,0,0,0)   // ViewFrame frame_,
                                      , ArgbColor(0,0,0,0)   // ArgbColor bgcolor_,
                                      , -1                   // int32_t fontsize_,
                                      , TextAlign::NONE      // TextAlign textalign_,
                                      , TextBoarder::NONE    // TextBoarder textboarder_,
                                      , ""                   // std::string text_,
                                      , false                // numericText
                                      , TextKeyboard::DEFAULT// keyboardtype
                                      , std::vector<ViewConstraint>()
                                      , std::unordered_map<std::string, ViewConf>()
                    ));
}
*/