//
//  ring.cpp
//  thesisFinalSketch
//
//  Created by Eric Jiang on 4/3/16.
//
//

#include "ring.h"

ring::ring(){
 
}

void ring::setup(string name){
    parameters.setName(name);
    parameters.add(size.set("size",150, 0, 500));
    parameters.add(pos.set("position",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
}


void ring::draw(){
    ofSetLineWidth(3);
    ofNoFill();
    ofDrawCircle(pos.get(), size);
    ofFill();
    ofSetColor(0, 255, 0);
    ofDrawCircle(pos.get(),3);

}

ofVec2f ring::getCenter(){
    return pos;
}

int ring::getSize(){
    return size;
}