//
//  instance_getter_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/25/16.
//
//

#include <map>

#include "instance_getter_gen.hpp"
#include "camera_controller_gen.hpp"
#include "platform_utility_gen.hpp"
#include "config_imp.hpp"
#include "macro.h"

using namespace gearsbox;

static std::shared_ptr<CameraControllerGen> s_camera_controller = nullptr;
std::shared_ptr<CameraControllerGen> InstanceGetterGen::getCameraController(){
    CHECK_RTNULL(s_camera_controller!=nullptr, "s_camera_controller not set");
    return s_camera_controller;
}

void InstanceGetterGen::setCameraController(const std::shared_ptr<CameraControllerGen> & camera){
    s_camera_controller = camera;
}

static std::shared_ptr<PlatformUtilityGen> s_platorm_utility = nullptr;
std::shared_ptr<PlatformUtilityGen> InstanceGetterGen::getPlatformUtility(){
    CHECK_RTNULL(s_camera_controller!=nullptr, "s_platorm_utility not set");
    return s_platorm_utility;
}

void InstanceGetterGen::setPlatformUtility(const std::shared_ptr<PlatformUtilityGen> & platform){
    s_platorm_utility = platform;
}

static std::shared_ptr<DeviceGen> s_device = nullptr;
std::shared_ptr<DeviceGen> InstanceGetterGen::getDevice(){
    CHECK_RTNULL(s_camera_controller!=nullptr, "s_device not set");
    return s_device;
}

void InstanceGetterGen::setDevice(const std::shared_ptr<DeviceGen> & device){
    s_device = device;
}

typedef std::map<std::string, std::shared_ptr<ConfigGen> > MAP_CONFIG_GEN ;
static MAP_CONFIG_GEN s_map_config_gen;
std::shared_ptr<ConfigGen> InstanceGetterGen::getConfig(const std::string & id){
    
    MAP_CONFIG_GEN::iterator find(s_map_config_gen.find(id));
    if (find!=s_map_config_gen.end()){
        return s_map_config_gen[id];
    }
    
    s_map_config_gen[id] = std::make_shared<ConfigImp>();
    return s_map_config_gen[id];
}
