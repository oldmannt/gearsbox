//
//  ui_conf_imp.cpp
//  gearsbox
//
//  Created by dyno on 6/5/16.
//
//

#include "ui_conf_imp.hpp"
#include "view_constraint.hpp"
#include "view_conf.hpp"
#include "view_type.hpp"
#include "ILog.h"
#include <fstream>

namespace gearsbox {
    
std::shared_ptr<UiConfGen> UiConfGen::instance(){
    static std::shared_ptr<UiConfGen> s_ptr = std::make_shared<UiConfImp>();
    return s_ptr;
}

UiConfImp::UiConfImp():m_init(false){
    
}

UiConfImp::~UiConfImp(){
    m_conf.viewconfs.clear();
    m_conf.predef_constraints.clear();
}

bool UiConfImp::initialize(const std::string& cfg){
    if (m_init) return false;
    m_init = true;
    return this->load(cfg);
}

bool UiConfImp::load(const std::string& cfg){
    Reader reader;
    return reader.readFile(cfg, m_conf);
}

std::vector<ViewConstraint>  UiConfImp::getConstraints(const std::string & name) const{
    MapConstraints::const_iterator find = m_conf.predef_constraints.find(name);
    if (find == m_conf.predef_constraints.end())
        return std::vector<ViewConstraint>();
    return m_conf.predef_constraints.at(name);
}

ViewConf UiConfImp::getViewConf(const std::string &name) const{
    if (m_conf.viewconfs.find(name) == m_conf.viewconfs.end()){
        return ViewConf();
    }
    return m_conf.viewconfs.at(name);
}
    
bool UiConfImp::Reader::readFile(const std::string &cfg, UiConfData& data){
    std::ifstream ifs(cfg);
    if (!ifs.is_open()){
        G_LOG_FC(LOG_ERROR, "open cfg failed %s", cfg.c_str());
        return false;
    }
    
    std::string buffer;
    std::getline(ifs, buffer, (char)EOF);
    return readBuffer(buffer, data);
}

bool UiConfImp::Reader::readBuffer(const std::string& buffer, UiConfData& data){
    Json::Value json_cfg;
    Json::Reader json_reader;
    if (!json_reader.parse(buffer, json_cfg)){
        std::string err = json_reader.getFormatedErrorMessages();
        G_LOG_FC(LOG_ERROR, "parse cfg failed err:%s", json_reader.getFormatedErrorMessages().c_str());
        return false;
    }
    
    try {
        Json::Value& constraints_json = json_cfg["constraints"];
        Json::Value::Members mem = constraints_json.getMemberNames();
        Json::Value::Members::iterator it(mem.begin());
        for (; it!=mem.end(); ++it){
            std::string predef_name = *it;
            Json::Value& constraint_array_json = constraints_json[predef_name];
            
            if (constraint_array_json.type()!=Json::ValueType::arrayValue){
                G_LOG_FC(LOG_ERROR, "parse constraints failed [%s] is not array", predef_name.c_str());
                continue;
            }
            
            std::vector<ViewConstraint> vec_consttraints;
            vec_consttraints.reserve(constraint_array_json.size());
            for (Json::ArrayIndex i=0; i<constraint_array_json.size(); ++i) {
                ViewConstraint view_consttraint;
                if (!readConstraint(constraint_array_json[i], view_consttraint))
                    continue;
                vec_consttraints.push_back(view_consttraint);
            }
            data.predef_constraints[predef_name] = vec_consttraints;
            G_LOG_FC(LOG_INFO, "parse array [%s] %d constraints ", predef_name.c_str(), vec_consttraints.size());
        }
        
        Json::Value& views_json = json_cfg["views"];
        if (views_json.type()!=Json::ValueType::arrayValue){
            G_LOG_FC(LOG_ERROR, "parse views failed is not array");
        }
        else{
            for (Json::ArrayIndex i=0; i<views_json.size(); ++i) {
                ViewConf view_conf;
                if (!readView(views_json[i], view_conf))
                    continue;
                data.viewconfs[view_conf.id] = view_conf;
                G_LOG_FC(LOG_INFO, "parse view [%s]", view_conf.id.c_str());
            }
            
        }

    } catch (std::exception& ex) {
        G_LOG_FC(LOG_ERROR, "read json::Value exception:%s", ex.what());
        return false;
    }
    
    return true;
}

    ConstraintType getConstraintType(const std::string& str){
        if ("top" == str)   return ConstraintType::TOP;
        else if ("leading" == str) return ConstraintType::LEADING;
        else if ("trailing" == str) return ConstraintType::TRAILING;
        else if ("bottom" == str) return ConstraintType::BOTTOM;
        else if ("width" == str) return ConstraintType::WIDTH;
        else if ("height" == str) return ConstraintType::HEIGHT;
        else if ("centerx" == str) return ConstraintType::CENTERX;
        else if ("centery" == str) return ConstraintType::CENTERY;
        else if ("" == str)        return ConstraintType::NONE;
        else{
            G_LOG_FC(LOG_ERROR, "parse constraint type exception str:%s", str.c_str());
        }
    }

bool UiConfImp::Reader::readConstraint(const Json::Value& cfg, ViewConstraint& constraint){
    //{"from":"exchange_info","to":"first_us_unit","type_from":"height","type_to":"height","multiplier":1,"offset":0},
    
    try{
        constraint.view_from = cfg["from"].asString();
        constraint.view_to = cfg["to"].asString();
        constraint.type = getConstraintType(cfg["type_from"].asString());
        constraint.type_to = getConstraintType(cfg["type_to"].asString());
        constraint.multiplier = cfg["multiplier"].asFloat();
        constraint.offset = cfg["offset"].asFloat();
    }
    catch (std::exception &ex){
        G_LOG_FC(LOG_ERROR, "parse constraint exception:%s", ex.what());
        return false;
    }
    catch (...){
        G_LOG_FC(LOG_ERROR, "parse constraint unknow exception");
        return false;
    }
    
    G_LOG_FC(LOG_INFO, "frome:%s to:%s type:%d typeto:%d mul:%02f off:%02f", constraint.view_from.c_str(),
        constraint.view_to.c_str(), constraint.type, constraint.type_to, constraint.multiplier, constraint.offset);
    return true;
}
    ViewType getViewType(const std::string& str){
        if ("base" == str)   return ViewType::BASE;
        else if ("btn" == str) return ViewType::BTN;
        else if ("input" == str) return ViewType::INPUT;
        else if ("label" == str) return ViewType::LABEL;
        else{
            G_LOG_FC(LOG_ERROR, "parse view type exception str:%s", str.c_str());
        }
    }

bool UiConfImp::Reader::readView(const Json::Value& cfg, ViewConf& view){
    try {
        view.id = cfg["id"].asString();
        view.type = getViewType(cfg["type"].asString());
    }
    catch (std::exception &ex){
        G_LOG_FC(LOG_ERROR, "parse view request exception:%s", ex.what());
        return false;
    }
    catch (...){
        G_LOG_FC(LOG_ERROR, "parse view request unknow exception");
        return false;
    }
    
    try {
        this->readViewFrame(cfg["frame"], view.frame);
        view.textboarder = TextBoarder(cfg["text_boarder"].asInt());
        view.fontsize = cfg["fontsize"].asInt();
        view.textalign = TextAlign(cfg["textalign"].asInt());
        
        const Json::Value& constraints_json = cfg["constraints"];
        for (Json::ArrayIndex i=0; i<constraints_json.size(); ++i) {
            if (constraints_json[i].type() == Json::ValueType::nullValue){
                G_LOG_FC(LOG_ERROR, "parse constraints in view json null %d", i);
                continue;
            }
            ViewConstraint view_constraint;
            if (!this->readConstraint(constraints_json[i], view_constraint)){
                G_LOG_FC(LOG_ERROR, "parse constraints in view json failed %d", i);
                continue;
            }
            view.constraints.push_back(view_constraint);
        }
        G_LOG_FC(LOG_INFO, "parse %d constraints in views [%s], ", view.constraints.size(), view.id.c_str());
        
        const Json::Value& views_json = cfg["views"];
        for (Json::ArrayIndex i=0; i<views_json.size(); ++i) {
            if (views_json[i].type() == Json::ValueType::nullValue){
                G_LOG_FC(LOG_ERROR, "parse subview json null %d", i);
                continue;
            }
            ViewConf subview;
            if (!this->readView(views_json[i], subview)){
                G_LOG_FC(LOG_ERROR, "parse subview in view json failed %d", i);
                continue;
            }
            view.subviews[subview.id] = subview;
            G_LOG_FC(LOG_INFO, "parse subview [%s] in views [%s], ", subview.id.c_str(), view.id.c_str());
        }
        
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_INFO, "parse view miss not request property:%s", ex.what());
    }
    
    return true;
}
    
bool UiConfImp::Reader::readViewFrame(const Json::Value &cfg, gearsbox::ViewFrame &frame){
    try {
        frame.x = cfg[1].asFloat();
        frame.y = cfg[2].asFloat();
        frame.w = cfg[3].asFloat();
        frame.h = cfg[4].asFloat();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "parse view frame exception:%s", ex.what());
        return false;
    }
    
    return true;
}
    
}
