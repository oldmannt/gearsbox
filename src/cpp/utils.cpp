//
//  utils.cpp
//  gearsbox
//
//  Created by dyno on 6/23/16.
//
//

#include <fstream>
#include <chrono>
#include "macro.h"
#include "utils.hpp"

using namespace gearsbox;

bool gearsbox::readJson(const std::string& param, Json::Value& config){
    CHECK_RTF(param.size()>0, "param size 0");
    Json::Reader reader;
    const char* subfix = param.c_str()+param.size()-strlen(".json");
    if (0==strcmp(subfix, ".json")){
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

long long gearsbox::nowMilli(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}


#include <mach/mach_time.h>
uint64_t subtractTimes( uint64_t elapsed )
{
    static mach_timebase_info_data_t    sTimebaseInfo;
    
    // Convert to nanoseconds.
    
    // If this is the first time we've run, get the timebase.
    // We can use denom == 0 to indicate that sTimebaseInfo is
    // uninitialised because it makes no sense to have a zero
    // denominator is a fraction.
    
    if ( sTimebaseInfo.denom == 0 ) {
        (void) mach_timebase_info(&sTimebaseInfo);
    }
    
    // Do the maths. We hope that the multiplication doesn't
    // overflow; the price you pay for working in fixed point.
    
    uint64_t elapsedNano = elapsed * sTimebaseInfo.numer / sTimebaseInfo.denom;
    
    return elapsedNano;
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
