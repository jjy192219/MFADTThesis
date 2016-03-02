#pragma once

#include "ofMain.h"
#include "Cell.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioOn(int x, int y);
    void audioOff(int x, int y);
    void loadSounds();
    void nextStep();
    void intersect();
    
    bool setState = false;
    
    int mRow, mColumn; // number of cloumns and rows on canvas
    int mGridTop, mGridLeft, mGridWidth, mGridHeight;
    int mCurColumn; //current column tracker
    int mInitTimer;
    int mDuration;//sequncer step durations.
    
    int nearThreshold;
    int farThreshold;
    int angle;
    
    
    float mPerCellWidth, mPerCellHeight;
    
    Cell mGrid[5][5];// 3 by 5 grid, arry in cell type
    
    std::map <int, vector<ofSoundPlayer> >mSounds;//two dimensial vector for loading all the sounds
    
    std::map <int, vector<ofRectangle> >mRects;
    
    ofxKinect kinect;
    
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvGrayscaleImage finalGryImg;
    
    ofxCvContourFinder contourFinder;//gray image with full winow sizes
};