//
//  position.cpp
//  finalSketchIRLed
//
//  Created by Eric Jiang on 4/26/16.
//
//

#include "position.h"
#include "ofxPS3EyeGrabber.h"



position::position(){
    
}

void position::setup(){
    
    mVidGrabber.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    mVidGrabber.setup(640, 480);
    mColorImg.allocate(640, 480);
    mGrayImage.allocate(640, 480);
    mFinalGrayImage.allocate(ofGetWidth(), ofGetHeight());
    mThreshold = 50;
    
}

void position::update(){
    mVidGrabber.update();
    if (mVidGrabber.isFrameNew()) {
        mBlobCenters.clear();
        mColorImg.setFromPixels(mVidGrabber.getPixels());
        mGrayImage = mColorImg;
        mGrayImage.threshold(mThreshold);
        mFinalGrayImage.scaleIntoMe(mGrayImage);
        mContourFinder.findContours(mFinalGrayImage, 0, (ofGetWidth()*ofGetHeight())/3, 2, false);
        for (int i = 0; i < mContourFinder.nBlobs; i ++) {
            ofVec2f tempBlob  = mContourFinder.blobs[i].centroid;
            mBlobCenters.push_back(tempBlob);
        }
    }
}

float position::getIntersectDist(ofVec2f centerPos){
    if(mBlobCenters.size()>0){
        mMidPoint = (mBlobCenters[0]+ mBlobCenters[1])/2;
        mDisToCenter= (mMidPoint - centerPos).length();
    }
    return mDisToCenter;
}

void position::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofFill();
    ofSetLineWidth(2.0);
    mFinalGrayImage.draw(0,0);
    mContourFinder.draw(0,0, ofGetWidth(), ofGetHeight());
    ofDrawLine(mBlobCenters[0].x, mBlobCenters[0].y, mBlobCenters[1].x, mBlobCenters[1].y);
    ofDrawCircle(mMidPoint, 5);
}