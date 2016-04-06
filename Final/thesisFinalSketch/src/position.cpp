//
//  position.cpp
//  thesisFinalSketch
//
//  Created by Eric Jiang on 4/3/16.
//
//

#include "position.h"


position::position(){

}

void position::setup(){
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();		// opens first available kinect
    //kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    finalGryImg.allocate(ofGetWidth(), ofGetHeight());
    
    nearThreshold = 240;
    farThreshold = 230;
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    disToCenter = 0;
    

}

void position::update(int nearT, int farT, int tilt){
    nearThreshold = nearT;
    farThreshold  = farT;
    angle = tilt;
    kinect.update();
    
    if (kinect.isFrameNew()) {
        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(nearThreshold, true);
        grayThreshFar.threshold(farThreshold);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        
        // update the cv images
        grayImage.flagImageChanged();
        
        //convert kinectsized grayimage to of canvas size
        finalGryImg.scaleIntoMe(grayImage);
    }
}



float position::getIntersectDist(ofVec2f center){
    contourFinder.findContours(finalGryImg, 10, (kinect.width*kinect.height)/2, 1, false);
    
    for (int i = 0; i < contourFinder.nBlobs; i++) {
        ofVec2f temp(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
        disToCenter = (temp - center).length();
    }
    
    return disToCenter;

}

int position::getNBlobs(){
    return contourFinder.nBlobs;
}

void position::draw(){
    kinect.draw(0, 0, ofGetWidth(), ofGetHeight());
    contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
}

