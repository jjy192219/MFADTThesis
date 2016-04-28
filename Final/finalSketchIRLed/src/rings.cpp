//
//  rings.cpp
//  finalSketchIRLed
//
//  Created by Eric Jiang on 4/28/16.
//
//

#include "rings.h"

rings::rings(){
    
}

void rings::setup(string name){
    parameters.setName(name);
    parameters.add(size.set("size",150, 0, 500));
    parameters.add(pos.set("position",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
}


void rings::draw(){
    ofSetLineWidth(3);
    ofNoFill();
    ofDrawCircle(pos.get(), size);
    ofFill();
    ofSetColor(0, 255, 0);
    ofDrawCircle(pos.get(),10);
    
}

ofVec2f rings::getCenter(){
    return pos;
}

int rings::getSize(){
    return size;
}