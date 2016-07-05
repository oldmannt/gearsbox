//
//  user_config_imp.hpp
//  gearsbox
//
//  Created by dyno on 6/17/16.
//
//

#pragma once

#include "config_gen.hpp"
#include "json/json.h"
#include <map>

namespace gearsbox {
    
class ConfigImp:public ConfigGen {
public:
    ConfigImp();
    virtual ~ConfigImp() {}
       
    virtual bool initialize(const std::string & param);
    
    virtual std::string getString(const std::string & type);
    
    virtual int32_t getInt(const std::string & type);
    
    virtual float getFloat(const std::string & type);
    
    virtual int64_t getI64(const std::string & type);
    
    virtual void setString(const std::string & type, const std::string & value);
    
    virtual void setInt(const std::string & type, int32_t value);
    
    virtual void setFloat(const std::string & type, float value);
    
    virtual void setI64(const std::string & type, int64_t value);
private:
    //template<typename T>
    //void setValue(const std::string& key, const T& value);
    void save();
private:
    typedef std::map<std::string, std::string> MAP_STR;
    
    MAP_STR m_str_config;
    Json::Value m_config;
    std::string m_config_path;
};
    
}  // namespace gearsbox

