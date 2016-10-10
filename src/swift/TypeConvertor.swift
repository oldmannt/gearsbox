//
//  TypeConvertor.swift
//  usnit_app
//
//  Created by dyno on 6/6/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit

class  GBTyperConvertor {

    static func convertUIColor(_ color: GBArgbColor)-> UIColor{
        return UIColor(red: CGFloat(color.r),
                green: CGFloat(color.g),
                blue: CGFloat(color.b),
                alpha: CGFloat(color.a))
    }
    
    static func convertUIColor(_ color: GBArgbColor)-> CGColor{
        return UIColor(red: CGFloat(color.r),
                       green: CGFloat(color.g),
                       blue: CGFloat(color.b),
                       alpha: CGFloat(color.a)).cgColor
    }
    
    static func convertUIRect(_ rect: GBViewFrame)-> CGRect{
       return CGRect(x: CGFloat(rect.x), y: CGFloat(rect.y),
               width: CGFloat(rect.w), height: CGFloat(rect.h))
    }
    
    static func convertUIConstraintType(_ type: GBConstraintType)-> NSLayoutAttribute{
       
        var attr:NSLayoutAttribute = NSLayoutAttribute.notAnAttribute
        switch type {
        case GBConstraintType.leading:
            attr = NSLayoutAttribute.leading
            break
        case GBConstraintType.trailing:
            attr = NSLayoutAttribute.trailing
            break
        case GBConstraintType.top:
            attr = NSLayoutAttribute.top
            break
        case GBConstraintType.bottom:
            attr = NSLayoutAttribute.bottom
            break
        case GBConstraintType.width:
            attr = NSLayoutAttribute.width
            break
        case GBConstraintType.height:
            attr = NSLayoutAttribute.height
            break
        case GBConstraintType.centerX:
            attr = NSLayoutAttribute.centerX
            break
        case GBConstraintType.centerY:
            attr = NSLayoutAttribute.centerY
            break
        default: break
        }
        return attr
    }
    
    static func convertUITextBoarder(_ type: GBTextBoarder)->UITextBorderStyle{
        switch type {
        case GBTextBoarder.line:
            return UITextBorderStyle.line;
        case GBTextBoarder.bezel:
            return UITextBorderStyle.bezel
        case GBTextBoarder.roundedRect:
            return UITextBorderStyle.roundedRect
        default:
            return UITextBorderStyle.none
        }
    }
    
    static func convertUITextAlign(_ type: GBTextAlign) ->NSTextAlignment?{
        switch type {
        case GBTextAlign.left:
            return NSTextAlignment.left
        case GBTextAlign.center:
            return NSTextAlignment.center
        case GBTextAlign.right:
            return NSTextAlignment.right
        default:
            return nil;
        }
    }
    
    static func convertKeyboardType(_ type: GBTextKeyboard)->UIKeyboardType{
        switch type {
        case GBTextKeyboard.default:
            return UIKeyboardType.default
        case GBTextKeyboard.ASCII:
            return UIKeyboardType.asciiCapable
        case GBTextKeyboard.decimalPad:
            return UIKeyboardType.decimalPad
        case GBTextKeyboard.numberPad:
            return UIKeyboardType.numberPad
        case GBTextKeyboard.phonePad:
            return UIKeyboardType.phonePad
        case GBTextKeyboard.URL:
            return UIKeyboardType.URL
        }
    }
}
