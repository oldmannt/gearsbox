//
//  language_store_imp.hpp
//  gearsbox
//
//  Created by dyno on 6/16/16.
//
//

#pragma once

#include "language_store_gen.hpp"
#include "lang_type.hpp"

#include <map>

namespace gearsbox {
    

class LanguageStoreImp : public LanguageStoreGen{
public:
    LanguageStoreImp();
    virtual ~LanguageStoreImp() {}
    
    virtual bool initialize(const std::string & param);
    virtual void setLanguage(LangType lang);
    virtual LangType getLanguage();
    virtual std::string getString(const std::string & type);
    
private:
    
    
private:
    struct LangData{
        std::string chs;
        std::string eng;
    };
    typedef std::map<LangType, std::string> MAP_TYPE;
    typedef std::map<std::string, MAP_TYPE> MAP_LANG;
    
    LangType m_curent_lang;
    MAP_LANG m_lang_data;
};
    
}  // namespace gearsbox
