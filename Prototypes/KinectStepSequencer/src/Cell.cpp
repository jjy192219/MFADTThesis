//
//  Cell.cpp
//  StepSequencer
//
//  Created by Jingying Jiang on 3/1/16.
//
//

#include "Cell.h"


void Cell::setup(int x , int y){
    mX = x;
    mY = y;
    mState = false;
    mSelected = false;
    bSlider = false;
}

void Cell::cellOn(){
    mAudioOn = true;
}

void Cell::cellOff(){
    mAudioOn = false;
}

void Cell::sliderOn(){
    bSlider = true;
}

void Cell::sliderOff(){
    bSlider = false;
}

void Cell::draw(int colWidth, int rowHeight, int gridTop, int gridLeft){
    ofRectangle rect( colWidth * mX + gridLeft, rowHeight* mY + gridTop, colWidth-gridLeft,  rowHeight-95);
    
    if (mAudioOn) {
        ofSetColor(215,0,0);
        ofFill();
        ofRect(rect);
    }
    
    else if (mSelected) {
        ofFill();
        ofSetColor(204 ,204, 204);
        ofRect(rect);
    }
    
    else if (bSlider) {
        ofNoFill();
        ofSetColor(0 , 0, 0);
        ofRect(rect);
    }else{
        ofNoFill();
        ofSetColor(204, 204, 204);
        ofRect(rect);
    }
}