//
//  ring.hpp
//  thesisFinalSketch
//
//  Created by Eric Jiang on 4/3/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"

class ring {
public:
    ring();
    void setup(ofVec2f center, int radius);
    void update(ofVec2f newPos, int newRadius);
    void draw();
    void getCenter();
    
    ofVec2f pos;
    int     size;
    
//    ofParameterGroup        parameters;
//    ofParameter<ofVec2f>    positions;
//    ofParameter<int>        circleSize;

};