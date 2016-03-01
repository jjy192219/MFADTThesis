#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // enable depth->video image calibration
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
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    //-------sound setup------------
    
    
    synthOne.loadSound("toneOne.mp3");
    synthTwo.loadSound("toneTwo.mp3");
    synthThree.loadSound("toneThree.mp3");
    synthFour.loadSound("toneFour.mp3");
    synthFive.loadSound("toneFive.mp3");
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    ofBackground(100, 100, 100);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
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

        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(finalGryImg, 10, (kinect.width*kinect.height)/2, 5, false);
        
        //-------blob maching-------
        for (int i = 0; i < contourFinder.nBlobs; i++) {
            
            if (contourFinder.blobs[i].centroid.y > ofGetHeight()/2-20 && contourFinder.blobs[i].centroid.y < ofGetHeight()/2+20) {
                bOverlapped = true;
            }
            else {
                bOverlapped = false;
            }
        }
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    

    ofSetColor(255, 255, 255);
    

    // draw from the live kinect
    kinect.draw(0, 0, ofGetWidth(), ofGetHeight());
    contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
        
        
    grayImage.draw(ofGetWidth()-200, ofGetHeight()-150, 200, 150);
    contourFinder.draw(ofGetWidth()-200, ofGetHeight()-150, 200, 150);
    
   //----five lines on widnow------
    ofFill();
    ofRectangle rect1(0,ofGetHeight()/6,ofGetWidth(),5);
    ofRectangle rect2(0,ofGetHeight()/6*2,ofGetWidth(),5);
    ofRectangle rect3(0,ofGetHeight()/6*3,ofGetWidth(),5);
    ofRectangle rect4(0,ofGetHeight()/6*4,ofGetWidth(),5);
    ofRectangle rect5(0,ofGetHeight()/6*5,ofGetWidth(),5);
    
    
    //----actual drawing----------
    ofRect(rect1);
    ofRect(rect2);
    ofRect(rect3);
    ofRect(rect4);
    ofRect(rect5);

    
    
    
    //blobs & lines matching
    for (int i = 0; i < contourFinder.nBlobs; i++) {
        ofCircle(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, 10);
        
        if (contourFinder.blobs[i].boundingRect.intersects(rect1)) {
            ofSetColor(255, 0, 0);
            ofRect(rect1);
            bPlayOne = true;
        }else{
            bPlayOne = false;
        }
        
        if (contourFinder.blobs[i].boundingRect.intersects(rect2)) {
            ofSetColor(255, 0, 0);
            ofRect(rect2);
            bPlayTwo = true;
        }else{
            bPlayTwo = false;
        }
        if (contourFinder.blobs[i].boundingRect.intersects(rect3)) {
            ofSetColor(255, 0, 0);
            ofRect(rect3);
            bPlayThree = true;
        }else{
            bPlayThree = false;
        }
        if (contourFinder.blobs[i].boundingRect.intersects(rect4)) {
            ofSetColor(255, 0, 0);
            ofRect(rect4);
            bPlayFour= true;
        }else{
            bPlayFour = false;
        }
        if (contourFinder.blobs[i].boundingRect.intersects(rect5)) {
            ofSetColor(255, 0, 0);
            ofRect(rect5);
            bPlayFive = true;
        }else{
            bPlayFive = false;
        }
        
        playSound(i);
        
    }


    
    
    // draw instructions
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    
    if(kinect.hasAccelControl()) {
        reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
        << ofToString(kinect.getMksAccel().y, 2) << " / "
        << ofToString(kinect.getMksAccel().z, 2) << endl;
    } else {
        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
        << "motor / led / accel controls are not currently supported" << endl << endl;
    }
    
    reportStream<< "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
    << ", fps: " << ofGetFrameRate() << endl
    << "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl;
    
    if(kinect.hasCamTiltControl()) {
        reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees"<< endl;
    }
    
    ofDrawBitmapString(reportStream.str(), 20, 652);
    
}


void ofApp::playSound(int i){
    synthOne.setMultiPlay(true);
    synthTwo.setMultiPlay(true);
    synthThree.setMultiPlay(true);
    synthFour.setMultiPlay(true);
    synthFive.setMultiPlay(true);
    
    float speed = ofMap(contourFinder.blobs[i].centroid.x, 0, ofGetWidth(), 0.5, 1.5);
//    cout<<"speed"<< speed <<std::endl;
    
    if (bPlayOne) {
        if (!synthOne.getIsPlaying()) {
            synthOne.play();
            synthOne.setSpeed(speed);
        }
    }

    
    if (bPlayTwo) {
        if (!synthTwo.getIsPlaying()) {
            synthTwo.play();
            synthTwo.setSpeed(speed);
        }
    }

    
    if (bPlayThree) {
        if (!synthThree.getIsPlaying()) {
            synthThree.play();
            synthThree.setSpeed(speed);
        }
    }

    if (bPlayFour) {
        if (!synthFour.getIsPlaying()) {
            synthFour.play();
            synthFour.setSpeed(speed);
        }
    }

    if (bPlayFive) {
        if (!synthFive.getIsPlaying()) {
            synthFive.play();
            synthFive.setSpeed(speed);
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
    switch (key) {
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
            
        case 'w':
            kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
            break;
            
        case 'o':
            kinect.setCameraTiltAngle(angle); // go back to prev tilt
            kinect.open();
            break;
            
        case 'c':
            kinect.setCameraTiltAngle(0); // zero the tilt
            kinect.close();
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{}
