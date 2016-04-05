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
    void setup(string name);
    void draw();
    ofVec2f getCenter();
    int     getSize();
    
    ofParameterGroup        parameters;
    ofParameter<ofVec2f>    pos;
    ofParameter<int>        size;

};