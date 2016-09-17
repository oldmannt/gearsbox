//
//  camera_config_imp.cpp
//  gearsbox
//
//  Created by dyno on 9/9/16.
//
//

#include "camera_config_imp.hpp"

#include "macro.h"

using namespace gearsbox;

std::shared_ptr<CameraConfigGen> CameraConfigGen::instance(){
    static std::shared_ptr<CameraConfigGen> s_ptr = std::make_shared<CameraConfigImp>();
    return s_ptr;
}

bool CameraConfigImp::initialize(const std::shared_ptr<ConfigGen> & cfg){
    CHECK_RTF(cfg!=nullptr, "cfg null");
    
    m_config = cfg;
    return true;
}

CameraFlash CameraConfigImp::getFlashMode(){
    CHECK_RTP(nullptr != m_config, CameraFlash::NONE, "m_config null");
    std::string mode = m_config->getString(CameraConfigGen::FLASH_MODE);
    if (mode == CameraConfigGen::FLASH_MODE_AUTO)
        return CameraFlash::AUTO;
    else if (mode == CameraConfigGen::FLASH_MODE_ON)
        return CameraFlash::ON;
    else if (mode == CameraConfigGen::FLASH_MODE_OFF)
        return CameraFlash::OFF;
    
    G_LOG_C(LOG_INFO, "error config(%s) for flash mode", mode.c_str());
    return CameraFlash::NONE;
}

CameraQuality CameraConfigImp::getQuatityLevel(){
    CHECK_RTP(nullptr != m_config, CameraQuality::NONE, "m_config null");
    std::string mode = m_config->getString(CameraConfigGen::QUALITY);
    if (mode == CameraConfigGen::QUALITY_360P) {
        return CameraQuality::P360;
    }
    else if (mode == CameraConfigGen::QUALITY_480P){
        return CameraQuality::P480;
    }
    else if (mode == CameraConfigGen::QUALITY_720P){
        return CameraQuality::P720;
    }
    else if (mode == CameraConfigGen::QUALITY_1080P){
        return CameraQuality::P1080;
    }
    
    G_LOG_C(LOG_INFO, "error config(%s) for camera quatity", mode.c_str());
    return CameraQuality::NONE;

}

void CameraConfigImp::setFlashMode(CameraFlash mode){
    CHECK_RT(nullptr != m_config, "m_config null");
    std::string text = "";
    switch (mode) {
        case CameraFlash::AUTO:
            text = CameraConfigGen::FLASH_MODE_AUTO;
            break;
        case CameraFlash::ON:
            text = CameraConfigGen::FLASH_MODE_ON;
            break;
        case CameraFlash::OFF:
            text = CameraConfigGen::FLASH_MODE_OFF;
            break;
            
        default:
            break;
    }
    m_config->setString(CameraConfigGen::FLASH_MODE, text);
}

void CameraConfigImp::setQuatityLevel(CameraQuality quality){
    CHECK_RT(nullptr != m_config, "m_config null");
    std::string text = "";
    switch (quality) {
        case CameraQuality::P360:
            text = CameraConfigGen::QUALITY_360P;
            break;
        case CameraQuality::P480:
            text = CameraConfigGen::QUALITY_480P;
            break;
        case CameraQuality::P720:
            text = CameraConfigGen::QUALITY_720P;
            break;
        case CameraQuality::P1080:
            text = CameraConfigGen::QUALITY_1080P;
            break;
        default:
            break;
    }
    m_config->setString(CameraConfigGen::QUALITY, text);
}