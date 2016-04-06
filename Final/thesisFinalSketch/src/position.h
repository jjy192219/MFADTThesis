//
//  position.hpp
//  thesisFinalSketch
//
//  Created by Eric Jiang on 4/3/16.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class position {
    public:
    position();
    
    void setup();
    void update(int nearTreash, int farTreash, int tiltAngle);
    void draw();
    float getIntersectDist(ofVec2f centerPos);
    int getNBlobs();
    
    ofxKinect           kinect;
    ofxCvColorImage     colorImg;
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    ofxCvGrayscaleImage finalGryImg;
    ofxCvContourFinder  contourFinder;//gray image with full winow sizes
    
    int                 nearThreshold;
    int                 farThreshold;
    int                 angle;
    float               disToCenter;
    
};
