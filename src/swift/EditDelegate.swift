//
//  EditDelegate.swift
//  usnit_app
//
//  Created by dyno on 7/2/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation

import Foundation
import UIKit

class EditDelegate: NSObject, UITextFieldDelegate {
    
    fileprivate var edtInput : UITextField?
    var m_delegates:[UITextFieldDelegate]=[]
    
    init(edt: UITextField){
        edtInput = edt;
    }
    
    func addDelegates(_ delegate:UITextFieldDelegate){
        m_delegates.append(delegate)
    }
    
    // Dismiss the keyboard when the user taps the "Return" key or its equivalent
    // while editing a text field.
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }
    
    func textField(_ textField: UITextField,
                   shouldChangeCharactersIn range: NSRange,
                                                 replacementString string: String)
        -> Bool
    {
        // We ignore any change that doesn't add characters to the text field.
        // These changes are things like character deletions and cuts, as well
        // as moving the insertion point.
        //
        // We still return true to allow the change to take place.
        if string.characters.count == 0 {
            return true
        }

        for delegate in m_delegates {
            if (!delegate.textField!(textField, shouldChangeCharactersIn: range, replacementString: string)){
                return false
            }
        }
        
        return true
    }
}
