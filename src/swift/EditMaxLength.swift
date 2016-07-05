//
//  File.swift
//  usnit_app
//
//  Created by dyno on 7/2/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit

class EditMaxLength: NSObject, UITextFieldDelegate {
    
    private var edtInput : UITextField?
    private var m_length:Int
    
    init(edt: UITextField, length:Int){
        edtInput = edt
        m_length = length
    }
    
    // Dismiss the keyboard when the user taps the "Return" key or its equivalent
    // while editing a text field.
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }
    
    func textField(textField: UITextField,
                   shouldChangeCharactersInRange range: NSRange,
                                                 replacementString string: String)
        -> Bool
    {
        let currentCharacterCount = textField.text?.characters.count ?? 0
        if (range.length + range.location > currentCharacterCount){
            return false
        }
        let newLength = currentCharacterCount + string.characters.count - range.length
        return newLength <= m_length

    }
}