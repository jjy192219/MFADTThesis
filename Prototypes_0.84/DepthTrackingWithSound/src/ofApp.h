#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"


class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void playSound(int index);
    
    ofxKinect kinect;
    
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvGrayscaleImage finalGryImg;
    
    ofxCvContourFinder contourFinder;//gray image with full winow sizes

    ofSoundPlayer  synthOne;
    ofSoundPlayer  synthTwo;
    ofSoundPlayer  synthThree;
    ofSoundPlayer  synthFour;
    ofSoundPlayer  synthFive;
    
    bool           bPlayOne;	
    bool           bPlayTwo;
    bool           bPlayThree;
    bool           bPlayFour;
    bool           bPlayFive;

    bool bOverlapped =false;
    
    int nearThreshold;
    int farThreshold;
    int angle;
    

};

