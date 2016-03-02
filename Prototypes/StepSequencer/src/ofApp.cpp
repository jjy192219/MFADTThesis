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
    
    int timeDiff = ofGetElapsedTimeMillis() - mInitTimer; //current time - initial timer
//    cout<<"timediff: "<<timeDiff<<std::endl;
    
    if (timeDiff > (mDuration*1000)) {
        nextStep();
        mInitTimer = ofGetElapsedTimeMillis(); //rest init timer to current time;
    }

}

void ofApp::nextStep(){
    

    
    mCurColumn = (mCurColumn + 1) % mColumn;
    
    for (int x = 0; x<mRow;x++) {
        for (int y = 0 ; y< mColumn;y++) {
            
            if (mGrid[x][y].mX == mCurColumn) {
                mGrid[x][y].sliderOn();
                if (mGrid[x][y].mState) {
                    mGrid[x][y].cellOn();
                    audioOn(x, y);
                }
            }
            else{
                mGrid[x][y].sliderOff();
                mGrid[x][y].cellOff();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    for (int x = 0; x<mRow; x++) {
        for (int y =0; y<mColumn; y++) {
            Cell cell = mGrid[x][y];
            cell.draw(mPerCellWidth, mPerCellHeight, mGridTop, mGridLeft);
        }
    }
    ofCircle(ofGetMouseX(), ofGetMouseY(), 3);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    int mX = ofMap(int(mouseX- mGridLeft), 0, mGridWidth, 0, mColumn);
//    int mY = ofMap(int(mouseY - mGridTop), 0, mGridHeight, 0, mRow);
    int mY;
    
    if (mouseY>mGridTop && mouseY< mGridTop+ mPerCellHeight-95) {
        mY = 0;
    }else if(mouseY>mGridTop + mPerCellHeight && mouseY< mGridTop+ mPerCellHeight*2-95){
        mY = 1;
    }else if(mouseY>mGridTop + mPerCellHeight*2 && mouseY< mGridTop+ mPerCellHeight*3-95){
        mY = 2;
    }else if(mouseY>mGridTop + mPerCellHeight*3 && mouseY< mGridTop+ mPerCellHeight*4-95){
        mY = 3;
    }else if(mouseY>mGridTop + mPerCellHeight*4 && mouseY< mGridTop+ mPerCellHeight*5-95){
        mY = 4;
    }
    
    if(mX >= 0 && mX < mColumn && mY >= 0 && mY < mRow){
        setState = ! mGrid[mX][mY].mState;
        mGrid[mX][mY].mState = setState;
        mGrid[mX][mY].mSelected = setState;
    }


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
