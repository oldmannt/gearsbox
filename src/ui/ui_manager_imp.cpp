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
        return false;
    }
    m_viewFactory = factory;
    if (!UiConfGen::instance()->initialize(param))
        return false;

    return true;
}

void UiManagerImp::inject(const std::shared_ptr<ViewGen> &view){
    if (!m_viewFactory){
        G_LOG_FC(LOG_ERROR, "factory null");
        return;
    }
    if (!view){
        G_LOG_FC(LOG_ERROR, "view null");
        return;
    }
    if (!m_viewFactory->injectView(view)){
        G_LOG_FC(LOG_ERROR, "inject view fail");
        return;
    }
    
    m_mapView[view->getId()] = view;
}

std::shared_ptr<ViewGen> UiManagerImp::addView(const std::shared_ptr<ViewGen> & view){
    if (nullptr == view)
        return nullptr;
    
    if (m_mapView[view->getId()]!=nullptr){
        G_LOG_FC(LOG_ERROR, "view id %s already exist", view->getId().c_str());
        return nullptr;
    }
    
    m_mapView[view->getId()] = view;
}

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
        G_LOG_FC(LOG_ERROR, "id:%s dont' exist, nothing finded", id.c_str());
        return nullptr;
    }
    return it->second;

}