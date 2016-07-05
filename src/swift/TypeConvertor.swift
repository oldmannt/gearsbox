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

    static func convertUIColor(color: GBArgbColor)-> UIColor{
        return UIColor(red: CGFloat(color.r),
                green: CGFloat(color.g),
                blue: CGFloat(color.b),
                alpha: CGFloat(color.a))
    }
    
    static func convertUIColor(color: GBArgbColor)-> CGColor{
        return UIColor(red: CGFloat(color.r),
                       green: CGFloat(color.g),
                       blue: CGFloat(color.b),
                       alpha: CGFloat(color.a)).CGColor
    }
    
    static func convertUIRect(rect: GBViewFrame)-> CGRect{
       return CGRect(x: CGFloat(rect.x), y: CGFloat(rect.y),
               width: CGFloat(rect.w), height: CGFloat(rect.h))
    }
    
    static func convertUIConstraintType(type: GBConstraintType)-> NSLayoutAttribute{
       
        var attr:NSLayoutAttribute = NSLayoutAttribute.NotAnAttribute
        switch type {
        case GBConstraintType.Leading:
            attr = NSLayoutAttribute.Leading
            break
        case GBConstraintType.Trailing:
            attr = NSLayoutAttribute.Trailing
            break
        case GBConstraintType.Top:
            attr = NSLayoutAttribute.Top
            break
        case GBConstraintType.Bottom:
            attr = NSLayoutAttribute.Bottom
            break
        case GBConstraintType.Width:
            attr = NSLayoutAttribute.Width
            break
        case GBConstraintType.Height:
            attr = NSLayoutAttribute.Height
            break
        case GBConstraintType.CenterX:
            attr = NSLayoutAttribute.CenterX
            break
        case GBConstraintType.CenterY:
            attr = NSLayoutAttribute.CenterY
            break
        default: break
        }
        return attr
    }
    
    static func convertUITextBoarder(type: GBTextBoarder)->UITextBorderStyle{
        switch type {
        case GBTextBoarder.Line:
            return UITextBorderStyle.Line;
        case GBTextBoarder.Bezel:
            return UITextBorderStyle.Bezel
        case GBTextBoarder.RoundedRect:
            return UITextBorderStyle.RoundedRect
        default:
            return UITextBorderStyle.None
        }
    }
    
    static func convertUITextAlign(type: GBTextAlign) ->NSTextAlignment?{
        switch type {
        case GBTextAlign.Left:
            return NSTextAlignment.Left
        case GBTextAlign.Center:
            return NSTextAlignment.Center
        case GBTextAlign.Right:
            return NSTextAlignment.Right
        default:
            return nil;
        }
    }
    
    static func convertKeyboardType(type: GBTextKeyboard)->UIKeyboardType{
        switch type {
        case GBTextKeyboard.Default:
            return UIKeyboardType.Default
        case GBTextKeyboard.ASCII:
            return UIKeyboardType.ASCIICapable
        case GBTextKeyboard.DecimalPad:
            return UIKeyboardType.DecimalPad
        case GBTextKeyboard.NumberPad:
            return UIKeyboardType.NumberPad
        case GBTextKeyboard.PhonePad:
            return UIKeyboardType.PhonePad
        case GBTextKeyboard.URL:
            return UIKeyboardType.URL
        }
    }
}
