//
//  camera_config_imp.hpp
//  gearsbox
//
//  Created by dyno on 9/9/16.
//
//

#ifndef camera_config_imp_hpp
#define camera_config_imp_hpp

#include "camera_config_gen.hpp"
#include "camera_flash.hpp"
#include "camera_quality.hpp"
#include "config_gen.hpp"

namespace gearsbox {
    
class ConfigGen;
enum class CameraFlash;
enum class CameraQuality;

class CameraConfigImp : public CameraConfigGen {
public:
    virtual ~CameraConfigImp() {}
    CameraConfigImp():m_config(nullptr){
        
    }
    
    virtual bool initialize(const std::shared_ptr<ConfigGen> & cfg);
    
    virtual CameraFlash getFlashMode();
    
    virtual CameraQuality getQuatityLevel();
    
    virtual void setFlashMode(CameraFlash mode);
    
    virtual void setQuatityLevel(CameraQuality quality);
    
private:
    std::shared_ptr<ConfigGen> m_config;
};
    
}  // namespace gearsbox


#endif /* camera_config_imp_hpp */
