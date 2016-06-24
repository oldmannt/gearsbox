//
//  ui_conf_imp.hpp
//  gearsbox
//
//  Created by dyno on 6/5/16.
//
//

#ifndef ui_conf_imp_hpp
#define ui_conf_imp_hpp

#include "ui_conf_gen.hpp"
#include "text_keyboard.hpp"
#include "view_frame.hpp"
#include <unordered_map>
#include <vector>
#include "json/json.h"

namespace gearsbox {
class UiConfImp: public UiConfGen{
public:
    UiConfImp();
    virtual ~UiConfImp();
    
    virtual bool initialize(const std::string& cfg);
    virtual bool load(const std::string & cfg);
    virtual std::vector<ViewConstraint>  getConstraints(const std::string & name) const;
    virtual ViewConf getViewConf(const std::string & nmae) const;
    
private:
    typedef std::unordered_map<std::string, ViewConf> MapViewConf;
    typedef std::vector<ViewConstraint> VecConstraint;
    typedef std::unordered_map<std::string, VecConstraint> MapConstraints;
    struct UiConfData{
        MapViewConf viewconfs;
        MapConstraints predef_constraints;
    };
    
    bool m_init;
    UiConfData m_conf;
    
    class Reader {
    public:
        bool readFile(const std::string& cfg, UiConfData& data);
        bool readBuffer(const std::string& cfg, UiConfData& data);
    
    private:
        bool readConstraint(const Json::Value& cfg, ViewConstraint& constraint);
        bool readView(const Json::Value& cfg, ViewConf& view);
        bool readViewFrame(const Json::Value& cfg, ViewFrame& frame);
        TextKeyboard readTextKeyboard(const std::string& cfg);
    };
};
}
#endif /* ui_conf_imp_hpp */
