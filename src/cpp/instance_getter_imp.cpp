//
//  instance_getter_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/25/16.
//
//

#include "instance_getter_gen.hpp"
#include "camera_controller_gen.hpp"
#include "platform_utility_gen.hpp"

using namespace gearsbox;

static std::shared_ptr<CameraControllerGen> s_camera_controller = nullptr;
std::shared_ptr<CameraControllerGen> InstanceGetterGen::getCameraController(){
    return s_camera_controller;
}

void InstanceGetterGen::setCameraController(const std::shared_ptr<CameraControllerGen> & camera){
    s_camera_controller = camera;
}

static std::shared_ptr<PlatformUtilityGen> s_platorm_utility = nullptr;
std::shared_ptr<PlatformUtilityGen> InstanceGetterGen::getPlatformUtility(){
    return s_platorm_utility;
}

void InstanceGetterGen::setPlatformUtility(const std::shared_ptr<PlatformUtilityGen> & platform){
    s_platorm_utility = platform;
}
