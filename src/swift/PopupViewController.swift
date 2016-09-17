//
//  PopupViewController.swift
//  lapse_app
//
//  Created by dyno on 8/28/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import UIKit

class PopupViewController: UIViewController {
    
    var m_popbase:PopbaseUIViewController?
    
    func setPopbase(popbase:PopbaseUIViewController) -> Bool {
        if nil != m_popbase {
            return false
        }
        
        m_popbase = popbase
        return true
    }
    
    func dissmissPopup(animationType: SLpopupViewAnimationType) {
        m_popbase?.dismissPopupViewController(animationType)
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
