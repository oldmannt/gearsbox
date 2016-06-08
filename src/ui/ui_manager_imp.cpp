//
//  ui_injecter.cpp
//  gearsbox
//
//  Created by dyno on 5/25/16.
//
//

#include "ui_manager_imp.hpp"
#include "ui_conf_gen.hpp"
#include "view_conf.hpp"
#include "view_factory_gen.hpp"
#include "view_gen.hpp"
#include "ILog.h"

using namespace gearsbox;

std::shared_ptr<UiManagerGen> UiManagerGen::instance(){
    static std::shared_ptr<UiManagerGen> s_ptr = std::make_shared<UiManagerImp>();
    return s_ptr;
}

UiManagerImp::UiManagerImp():m_viewFactory(nullptr){
    
}

UiManagerImp::~UiManagerImp(){
    m_mapView.clear();
    m_viewFactory = nullptr;
}

bool UiManagerImp::initialize(const std::string & param, const std::shared_ptr<ViewFactoryGen> & factory){
    if (nullptr == factory){
        G_LOG_FC(LOG_ERROR, "factory null");
        //return false;
    }
    m_viewFactory = factory;
    if (!UiConfGen::instance()->initialize(param))
        return false;

    return true;
}

void UiManagerImp::inject(const std::string &id, const std::shared_ptr<ViewGen> &view){
    m_mapView[id] = view;
}

/*
std::shared_ptr<ViewGen> UiManagerImp::buldView(const std::string & id, const std::string & parent){
    std::shared_ptr<ViewGen> view_parent = getView(parent);
    if (nullptr == view_parent){
        G_LOG_FC(LOG_ERROR, "create view:%s parent:%s null failed", id.c_str(), parent.c_str());
        return nullptr;
    }
    
    ViewConf view_conf = UiConfGen::instance()->getViewConf(id);
    std::shared_ptr<ViewGen> view = m_viewFactory->createView(id, view_conf);
    if (nullptr == view){
        G_LOG_FC(LOG_ERROR, "create view:%s failed", id.c_str());
        return nullptr;
    }
    
}
*/

void UiManagerImp::removeView(const std::string &id){
    MapView::iterator it(m_mapView.find(id));
    if (it==m_mapView.end()){
        G_LOG_FC(LOG_ERROR, "id dont' exist, nothing to remove");
    }
    m_mapView.erase(it);
}

std::shared_ptr<ViewGen> UiManagerImp::getView(const std::string &id){
    MapView::iterator it(m_mapView.find(id));
    if (it==m_mapView.end()){
        G_LOG_FC(LOG_ERROR, "id dont' exist, nothing finded");
        return nullptr;
    }
    return it->second;

}