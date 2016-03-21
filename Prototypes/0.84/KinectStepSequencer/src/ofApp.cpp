#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mRow = 5;
    mColumn = 5;
    mGridTop = 105;
    mGridLeft = 0;
    mGridWidth = ofGetWidth() - (mGridLeft*2); //the width of whole grid
    mGridHeight =  ofGetHeight() - (mGridTop*2); //the height of whole grid
    mCurColumn = -1;
    mPerCellWidth = mGridWidth/mColumn; // size of each cell
    mPerCellHeight = mGridHeight/mRow;
    
    mInitTimer = ofGetElapsedTimeMillis();
    mDuration = 1;
    loadSounds();
    
    //initialize the grid
    for (int x = 0; x<mRow; x++) {
        for (int y = 0 ; y< mColumn; y++) {
            mGrid[x][y].setup(x, y);
        }
    }
    
    for (int i = 0 ; i < mRow; i ++) {
        for (int j = 0; j <mColumn; j++) {
            std::cout<<mGrid[i][j].mX<<mGrid[i][j].mY<< ' ';
        }
        std::cout << std::endl;
    }
    
//-----------------------------------kinect setup---------------------------------------
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


    
    
    
    
}

//-------------------------------------------------------------
void ofApp::loadSounds(){
    mSounds.clear();
    for (int x = 0; x< mRow; x++) {
        for (int y = 0; y<mColumn; y++) {
            ofSoundPlayer tempSound;
            string fileName = "tone"+ofToString(x)+"_"+ofToString(y)+".mp3";
            tempSound.loadSound(fileName);
            mSounds[x].push_back(tempSound);
        }
    }
}


void ofApp::audioOn(int x, int y){
    mSounds[x][y].play();
}



//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100, 100, 100);
    
    int timeDiff = ofGetElapsedTimeMillis() - mInitTimer; //current time - initial timer
    if (timeDiff > (mDuration*1000)) {
        mInitTimer = ofGetElapsedTimeMillis(); //rest init timer to current time;
        nextStep();
    }
    
//------------------------cv&kinect-----------------------------------
    // there is a new frame and we are connected
    kinect.update();
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

        intersect();

    }
}

void ofApp::intersect(){
    mRects.clear();
    mSelections.clear();
    contourFinder.findContours(finalGryImg, 10, (kinect.width*kinect.height)/2, 5, false);
    
    for (int i = 0; i < mRow; i ++) {
        for (int j = 0; j < mColumn; j ++) {
            ofRectangle rect(mPerCellWidth * i + mGridLeft, mPerCellHeight * j + mGridTop, mPerCellWidth - mGridLeft, mPerCellHeight - mGridTop - 95);
            mRects[i].push_back(rect);
        }
    }
    
    for (int x = 0; x < mRow; x ++) {
        for (int y = 0; y < mColumn; y ++) {
            for (int i = 0 ; i < contourFinder.nBlobs; i++) {
                if (contourFinder.blobs[i].boundingRect.intersects(mRects[x][y])) {
                    ofVec2f temp;
                    temp.set(x, y);
                    mSelections.push_back(temp);
                }else{
                    mGrid[x][y].mSelected = false;
                }
            }
        }
    }
    
    for (std::vector<ofVec2f>::iterator it = mSelections.begin(); it != mSelections.end(); it++) {
        mGrid[int(it->x)][int(it->y)].mSelected = true;
    }
}

void ofApp::nextStep(){
    mCurColumn = (mCurColumn + 1) % mColumn;
    
    for (int x = 0; x<mRow;x++) {
        for (int y = 0 ; y< mColumn;y++) {
            
            if (mGrid[x][y].mX == mCurColumn) {
                mGrid[x][y].sliderOn();
                if (mGrid[x][y].mSelected) {
                    mGrid[x][y].cellOn();
                    audioOn(x, y);
                }
            }else{
                mGrid[x][y].sliderOff();
                mGrid[x][y].cellOff();

            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw from the live kinect
    kinect.draw(0, 0, ofGetWidth(), ofGetHeight());
    contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    for (int x = 0; x<mRow; x++) {
        for (int y =0; y<mColumn; y++) {
            Cell cell = mGrid[x][y];
            cell.draw(mPerCellWidth, mPerCellHeight, mGridTop, mGridLeft);
        }
    }
    
    ofFill();
    ofCircle(ofGetMouseX(), ofGetMouseY(), 3);
    
    
//--------------------------------------------------------------------------------------
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    int mX = ofMap(int(mouseX- mGridLeft), 0, mGridWidth, 0, mColumn);
//    int mY;
//    
//    if (mouseY>mGridTop && mouseY< mGridTop+ mPerCellHeight-95) {
//        mY = 0;
//    }else if(mouseY>mGridTop + mPerCellHeight && mouseY< mGridTop+ mPerCellHeight*2-95){
//        mY = 1;
//    }else if(mouseY>mGridTop + mPerCellHeight*2 && mouseY< mGridTop+ mPerCellHeight*3-95){
//        mY = 2;
//    }else if(mouseY>mGridTop + mPerCellHeight*3 && mouseY< mGridTop+ mPerCellHeight*4-95){
//        mY = 3;
//    }else if(mouseY>mGridTop + mPerCellHeight*4 && mouseY< mGridTop+ mPerCellHeight*5-95){
//        mY = 4;
//    }
//    
//    if(mX >= 0 && mX < mColumn && mY >= 0 && mY < mRow){
//        setState = ! mGrid[mX][mY].mState;
//        mGrid[mX][mY].mState = setState;
//        mGrid[mX][mY].mSelected = setState;
//    }
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
