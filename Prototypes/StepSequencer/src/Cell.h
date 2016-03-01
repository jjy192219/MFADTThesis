//
//  Cell.h
//  StepSequencer
//
//  Created by Jingying Jiang on 3/1/16.
//
//
#pragma once

#include "ofMain.h"


class Cell {
public:
    
    void setup(int x, int y);
    void cellOn();
    void cellOff();
    void sliderOn();
    void sliderOff();
    void draw(int colWidth, int rowHeight, int gridTop, int gridLeft);
    void display();
    
//    ofColor mColorAudioOn;
//    ofColor mColorSelected;
//    ofColor mColorSlider;
//    ofColor mColorNothing;
    
    int mX, mY;
    bool mState;
    bool mAudioOn;
    bool mSelected;
    bool bSlider;

    
};