//
//  motions.hpp
//  thesisFinalSketch
//
//  Created by Eric Jiang on 4/4/16.
//
//

#pragma once
#include "ofMain.h"
#include "ofxSpacebrew.h"

class motions {
    public:
    motions();
    void setup();
    void onMessage( Spacebrew::Message & m );
    void playRake(int accel);
    void stopPlayRake();

    ofVec3f getRotations();
    ofVec3f getAccelerations();
    
    Spacebrew::Connection sb;
    string host, name, description;
    ofVec3f rotationRead;
    ofVec3f accelRead;
    
    ofSoundPlayer raking;
};
