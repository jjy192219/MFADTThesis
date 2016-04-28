//
//  position.hpp
//  finalSketchIRLed
//
//  Created by Eric Jiang on 4/26/16.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"


class position {
public:
    position();
    
    void setup();
    void update();
    void draw();
    float getIntersectDist(ofVec2f centerPos);
    int getNBlobs();
    
    
    ofVideoGrabber          mVidGrabber;
    ofxCvColorImage			mColorImg;
    ofxCvGrayscaleImage 	mGrayImage;
    ofxCvGrayscaleImage     mFinalGrayImage;
    ofxCvContourFinder      mContourFinder;
    int                     mThreshold;
    float                   mDisToCenter;
    ofVec2f                 mMidPoint;
    vector<ofVec2f>         mBlobCenters;
    
};
