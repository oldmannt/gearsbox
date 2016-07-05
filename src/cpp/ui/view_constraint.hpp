#pragma once


#include "view_constraint_base.hpp"


namespace gearsbox {
    
    struct ViewConstraint : public ViewConstraintBase
    {
        using ViewConstraintBase::ViewConstraintBase;
        
        ViewConstraint():
            ViewConstraintBase(ConstraintType::NONE,
                               ConstraintType::NONE,
                               "","",0.0f,0.0f){
            
        }
        
        ViewConstraint(ConstraintType type_,
                           ConstraintType type_to_,
                           std::string view_from_,
                           std::string view_to_,
                           float multiplier_,
                           float offset_)
        :ViewConstraintBase(type_, type_to_,view_from_,view_to_,multiplier_,offset_){
        }

    };
}