//
//  language_store_imp.cpp
//  gearsbox
//
//  Created by dyno on 6/16/16.
//
//

#include "language_store_imp.hpp"
#include "instance_getter_gen.hpp"
#include "platform_utility_gen.hpp"
#include "json/json.h"
#include "ilog.h"
#include "utils.hpp"

#include <fstream>

using namespace gearsbox;

std::shared_ptr<LanguageStoreGen> LanguageStoreGen::instance(){
    static std::shared_ptr<LanguageStoreGen> s_ptr = std::make_shared<LanguageStoreImp>();
    return s_ptr;
}

LanguageStoreImp::LanguageStoreImp():m_curent_lang(LangType::LANG_ENG){
    
}

LangType parseLangType(const std::string& param){
    if (param == "chs")
        return LangType::LANG_CHS;
    else if (param == "eng")
        return LangType::LANG_ENG;
    
    G_LOG_FC(LOG_ERROR, "unknow lang type:%s", param.c_str());
    return LangType::LANG_NONE;
}

bool LanguageStoreImp::initialize(const std::string & param){
    Json::Value conf;
    if (!readJson(param, conf))
        return false;
    
    std::string err_info;
    try {
        Json::Value::Members mem = conf.getMemberNames();
        Json::Value::Members::iterator it(mem.begin());
        for (; it!=mem.end(); ++it) {
            const std::string str_key = *it;
            err_info = str_key;
            
            Json::Value langs_conf = conf[str_key];
            MAP_TYPE map_lang_types;
            
            Json::Value::Members mem_types = langs_conf.getMemberNames();
            Json::Value::Members::iterator it_types(mem_types.begin());
            for (; it_types!=mem_types.end(); ++it_types) {
                LangType lang_type = parseLangType(*it_types);
                if (lang_type == LangType::LANG_NONE){
                    G_LOG_FC(LOG_ERROR, "lang err type");
                    continue;
                }
                
                map_lang_types.insert(std::make_pair(lang_type, langs_conf[*it_types].asString()));
                err_info += " " + *it_types;
            }

            m_lang_data[str_key] = map_lang_types;
        }
        
    } catch (std::exception &ex) {
        G_LOG_FC(LOG_ERROR, "read lang err:%s info;%s", ex.what(), err_info.c_str());
        return false;
    }
    return true;
}

void LanguageStoreImp::setLanguage(LangType lang){
    m_curent_lang = lang;
}

LangType LanguageStoreImp::getLanguage(){
    return m_curent_lang;
}

std::string LanguageStoreImp::getString(const std::string & type){
    MAP_LANG::iterator it_type( m_lang_data.find(type));
    if (it_type == m_lang_data.end()){
        G_LOG_FC(LOG_ERROR, "no define type in language;%s", type.c_str());
        return "";
    }
    
    //G_LOG_C(LOG_INFO, "get lang %s", type.c_str());
    //G_LOG_C(LOG_INFO, "lang item: %s", it_type->second[m_curent_lang].c_str());

    return it_type->second[m_curent_lang];
}

