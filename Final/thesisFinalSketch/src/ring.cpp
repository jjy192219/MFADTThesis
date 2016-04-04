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

void ring::setup(ofVec2f center, int radius){
    pos.set(center);
    size = radius;
    
}

void ring::update(ofVec2f newPos, int newRadius){
    pos.set(newPos);
    size = newRadius;
}

void ring::draw(){
    ofSetLineWidth(3);
    ofNoFill();
    ofCircle(pos, size);

}

void ring::getCenter(){
    return pos;
}