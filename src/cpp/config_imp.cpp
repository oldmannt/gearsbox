//
//  user_config_imp.cpp
//  gearsbox
//
//  Created by dyno on 6/17/16.
//
//

#include "config_imp.hpp"
#include "ilog.h"
#include "macro.h"
#include "utils.hpp"

#include <fstream>

using namespace gearsbox;

ConfigImp::ConfigImp():m_config(0){
    
}

ConfigImp::ConfigImp(std::shared_ptr<ConfigImp> parent):m_config(0), m_parent(parent){
    
}

ConfigImp::~ConfigImp(){
    if (nullptr == m_parent.lock()){
        delete m_config;
    }
}

std::shared_ptr<ConfigGen> ConfigGen::create(){
    return std::make_shared<ConfigImp>();
}

bool ConfigImp::initialize(Json::Value* node){
    CHECK_RTF(node!=nullptr,"node null");
    m_config = node;
    if (m_config->isArray() && m_config->size()>0 && m_array.empty()) {
        m_array.reserve(m_config->size());
        for (Json::ArrayIndex i = 0; i < m_config->size(); ++i) {
            Json::Value* json_node = nullptr;
            try {
                json_node = &((*m_config)[i]);
            } catch (std::exception &ex) {
                G_LOG_FC(LOG_ERROR, "initialize err:%s index:%s", ex.what(), index);
                continue;
            }
            
            CONTINUE(json_node!=nullptr && !json_node->isNull(),"json_node null index:%d", i);
            std::shared_ptr<ConfigImp> subconfig = std::make_shared<ConfigImp>();
            CONTINUE(subconfig->initialize(json_node), nullptr, "array config initialize failed index:%d", i);
            m_array.push_back(subconfig);
        }// end for
        return true;
    }
    
    if (m_config->isObject())
        return true;
    return false;
}

bool ConfigImp::initialize(const std::string & param){
    if (m_config!=nullptr)
        return false;
    m_config = new Json::Value();
    CHECK_RTF(readJson(param, *m_config), "readJson failed param:%s", param.c_str());
    m_config_path = param;
    G_LOG_C(LOG_INFO, "read config %d items, %s", (*m_config).size(), param.c_str());
    return true;
}

std::string ConfigImp::getString(const std::string & type){
    
    try {
        return (*m_config)[type].asString();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "getInt err:%s type:%s", ex.what(), type.c_str());
    }

    return "";
}

int32_t ConfigImp::getInt(const std::string & type){
    try {
        return (*m_config)[type].asInt();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "getInt err:%s type:%s", ex.what(), type.c_str());
    }
    
    return 0;
}

float ConfigImp::getFloat(const std::string & type){
    try {
        return (*m_config)[type].asFloat();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "getFolat err:%s type:%s", ex.what(), type.c_str());
    }
    
    return 0.0f;
}

int64_t ConfigImp::getI64(const std::string & type){
    try {
        return (*m_config)[type].asInt64();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "getI64 err:%s type:%s", ex.what(), type.c_str());
    }
    
    return 0;
}

bool ConfigImp::getBool(const std::string & type){
    try {
        return (*m_config)[type].asBool();
    } catch (std::exception &ex){
        G_LOG_FC(LOG_ERROR, "setBool err:%s type:%s", ex.what(), type.c_str());
    }
}

/*
template<typename T>
void ConfigImp::setValue(const std::string& key, const T& value){
    try {
        (*m_config)[key] = value;
        
        save();
        
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "setValue err:%s type:%s", ex.what(), typeid(value).name());
    }
}
*/

void ConfigImp::save(){
    if (auto parent = m_parent.lock()){
        parent->save();
        return;
    }
    if (m_config_path.empty())
        return;
    Json::FastWriter writer;
    std::string str = writer.write((*m_config));
    std::ofstream ofs;
    ofs.open(m_config_path);
    if (!ofs.is_open()){
        G_LOG_FC(LOG_ERROR, "open conf file failed: %s", m_config_path.c_str());
        m_config_path = "";
        return;
    }
    ofs << str;
    ofs.close();
}

void ConfigImp::setString(const std::string & type, const std::string & value){
    try {
        (*m_config)[type] = value;
        save();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "setValue err:%s type:%s", ex.what(), typeid(value).name());
    }

}

void ConfigImp::setInt(const std::string & type, int32_t value){
    try {
        (*m_config)[type] = value;
        save();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "setValue err:%s type:%s", ex.what(), typeid(value).name());
    }
}

void ConfigImp::setFloat(const std::string & type, float value){
    try {
        (*m_config)[type] = value;
        save();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "setValue err:%s type:%s", ex.what(), typeid(value).name());
    }
}

void ConfigImp::setI64(const std::string & type, int64_t value){
    try {
        (*m_config)[type] = Json::Value(Json::Int64(value));
        save();
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "setValue err:%s type:%s", ex.what(), typeid(value).name());
    }
}

void ConfigImp::setBool(const std::string & type, bool value){
    try {
        (*m_config)[type] = value;
    } catch (std::exception &ex){
        G_LOG_FC(LOG_ERROR, "setBool err:%s type:%s", ex.what(), type.c_str());
    }
}

int32_t ConfigImp::getArrayCount(){
    return m_array.size();
}

std::shared_ptr<ConfigGen> ConfigImp::getArrayItem(int32_t index){
    CHECK_RTNULL(m_array.size()>index, "out of range, index:%d", index);
    return m_array[index];
}

std::shared_ptr<ConfigGen> ConfigImp::getSubConfig(const std::string & key){
    MAP_CONFIG::iterator find = m_subNode.find(key);
    if (find!=m_subNode.end()){
        return find->second;
    }
    
    Json::Value* json_node = nullptr;
    try {
        json_node = &((*m_config)[key]);
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "getSubConfig err:%s key:%s", ex.what(), key.c_str());
        return nullptr;
    }
    
    CHECK_RTP(json_node, nullptr, "find object null key:%s file:%s",
              key.c_str(), m_config_path.c_str());
    CHECK_RTP(json_node->isObject() || json_node->isArray(),
              nullptr, "not object, key:%s file:%s", key.c_str(), m_config_path.c_str());
    
    std::shared_ptr<ConfigImp> subconfig = std::make_shared<ConfigImp>();
    CHECK_RTP(subconfig->initialize(json_node), nullptr, "sub config initialize failed key:%s file:%s", key.c_str(), m_config_path.c_str());
    
    m_subNode[key] = subconfig;
    
    return subconfig;
}
