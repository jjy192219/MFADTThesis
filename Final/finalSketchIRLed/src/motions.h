//
//  motions.hpp
//  finalSketchIRLed
//
//  Created by Eric Jiang on 4/28/16.
//
//

#pragma once
#include "ofMain.h"


class motions{
public:
    motions();
    void setup();
    void update();
    
//    ofVec3f getRotations();
//    ofVec3f getAccelerations();
//    
//    ofVec3f     mRotationRead;
//    ofVec3f     mAccelRead;
    ofSerial    mSerial;
    
};