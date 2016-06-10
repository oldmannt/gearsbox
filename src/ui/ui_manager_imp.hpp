//
//  ui_injecter.hpp
//  gearsbox
//
//  Created by dyno on 5/25/16.
//
//

#ifndef ui_injecter_hpp
#define ui_injecter_hpp

#include "ui_manager_gen.hpp"
#include "view_gen.hpp"

#include <map>
namespace gearsbox {

class UiManagerImp:public UiManagerGen{
public:
    UiManagerImp();
    virtual ~UiManagerImp();
    virtual bool initialize(const std::string & param, const std::shared_ptr<ViewFactoryGen> & factory);
    virtual void inject(const std::shared_ptr<ViewGen> & view);
    virtual std::shared_ptr<ViewGen> getView(const std::string & id);
    virtual std::shared_ptr<ViewGen> addView(const std::shared_ptr<ViewGen> & view);
    virtual void removeView(const std::string & id);
    
private:
    typedef std::map<std::string, std::shared_ptr<ViewGen>> MapView;
    std::shared_ptr<ViewFactoryGen> m_viewFactory;
    MapView m_mapView;
};
    
}

#endif /* ui_injecter_hpp */
