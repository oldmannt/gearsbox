//
//  MainLoop.swift
//  USNIT
//
//  Created by dyno on 5/3/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation

import UIKit

class MainLoop : NSObject {
    
    var doSomething: (Int64) -> ()!
    var displayLink : CADisplayLink!
    var frameInterval : Int!
    var last : Double!
    
    init(frameInterval: Int, doSomething: @escaping (Int64) -> ()) {
        self.doSomething = doSomething
        self.frameInterval = frameInterval
        last = CACurrentMediaTime()
        super.init()
        start()
    }
    
    // you could overwrite this too
    func handleTimer() {
        let now:Double = CACurrentMediaTime()
        //print("handleTimer \((now - last)*1000)")
        
        doSomething(Int64((now - last)*1000))
        last = now
    }
    
    func start() {
        displayLink = CADisplayLink(target: self, selector: #selector(MainLoop.handleTimer))
        displayLink.frameInterval = frameInterval
        displayLink.add(to: RunLoop.main, forMode: RunLoopMode.commonModes)
    }
    
    func stop() {
        displayLink.isPaused = true
        displayLink.remove(from: RunLoop.main, forMode: RunLoopMode.defaultRunLoopMode)
        displayLink = nil
    }
}
