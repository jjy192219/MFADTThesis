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
    void update(int thread);
    void draw();
    float getIntersectDist(ofVec2f centerPos);
    float getTravelSpeed();
    int getNBlobs();
    ofVec2f getMidPoint();
    
    
    ofVideoGrabber          mVidGrabber;
    ofxCvColorImage			mColorImg;
    ofxCvGrayscaleImage 	mGrayImage;
//    ofxCvGrayscaleImage     mFinalGrayImage;
    ofxCvContourFinder      mContourFinder;
    int                     mThreshold;
    float                   mDisToCenter;
    float                   mTimer;
    ofVec2f                 mMidPoint;
    vector<ofVec2f>         mBlobCenters;
    vector<ofVec2f>         mMidPoints;
    
};
