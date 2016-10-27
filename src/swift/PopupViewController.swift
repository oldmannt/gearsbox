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
    var m_overlay_view:UIView?
    var m_background_view:UIView?
    
    func setPopbase(popbase:PopbaseUIViewController) {
        if nil != m_popbase {
            GBLogGen.instance()?.logerrf("m_popbase not nil")
        }
        
        m_popbase = popbase
    }
    
    func dissmissPopup(animationType: SLpopupViewAnimationType) {
        m_popbase?.dismissPopupViewController(popup_ctl: self, animationType: animationType)
    }
    
    func isShowed() -> Bool{
        if m_popbase == nil || m_overlay_view == nil{
            return false
        }
        return m_popbase!.view.subviews.contains(m_overlay_view!)
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
