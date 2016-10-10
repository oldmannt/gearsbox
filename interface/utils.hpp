
#ifndef UTILS_hpp
#define UTILS_hpp

#include <string>
#include <sstream>
#include <memory>


#include "json/json.h"
#include "view_conf.hpp"

#ifdef __ANDROID__
// some stuff that belongs in the c++ stllib, but isn't
namespace std {
    // for some reason android doesn't ship with to_string implement it here
    template<typename T>
    std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
    
}
#endif

namespace gearsbox {
    bool readJson(const std::string& param, Json::Value& config);
    //ViewConf emptyViewConf();

}

#endif
