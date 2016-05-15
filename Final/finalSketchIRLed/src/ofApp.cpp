#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10);
    ofSetVerticalSync(true);
    ofBackground(255);
    bHide = false;
    bTouched1 = false;
    bTouched2 = false;
    bTouched3 = false;
    
    mRing1.setup("Ring 1");
    mRing2.setup("Ring 2");
    mRing3.setup("Ring 3");
    
    mParameters.setName("Setting");
    mParameters.add(mRing1.parameters);
    mParameters.add(mRing2.parameters);
    mParameters.add(mRing3.parameters);
    
    mGui.setup(mParameters);
    mGui.add(bSendNote.set("send note",false));
    mGui.add(notes.set("note val", 36, 0, 127));
    mGui.add(thread.set("Threashold", 50, 0, 100));
    
    position.setup();
    for (int i = 0; i < 3; i++) {
        distToCenter[i] = 0;
    }
    
    //-------midi----------
    midiOut.listPorts(); // via instance
    midiOut.openVirtualPort("Thesis MIDI");
    midiOut.sendControlChange(1, 21, 0);
    midiOut.sendControlChange(1, 22, 0);
    midiOut.sendControlChange(1, 23, 0);
    //--------motions----------
    motions.setup();
    rotationProcessedPrev = 0;
    rotationProcessed = 0;
    accelProcessedPrev = 0;
    accelProcessed = 0;
    
    mRackingSpeed = 0;
    //-----bell sounds-------
    
    mBell1.load("Bell Hi D.wav");
    mBell2.load("Bell Hi D.wav");
    mBell3.load("Bell Hi D.wav");

}

//--------------------------------------------------------------
void ofApp::update(){
    position.update(thread);
    
    //------------------distance between each rocks and the rake--------------
    distToCenter[0] = position.getIntersectDist(mRing1.getCenter());
    distToCenter[1]= position.getIntersectDist(mRing2.getCenter());
    distToCenter[2]= position.getIntersectDist(mRing3.getCenter());
    
    if (distToCenter[0] <= mRing1.getSize()) {
        bTouched1 = true;
    }else{
        bTouched1 = false;
    }
    
    if (distToCenter[1] <= mRing2.getSize()) {
        bTouched2 = true;
    }else{
        bTouched2 = false;
    }
    
    if (distToCenter[2] <= mRing3.getSize()) {
        bTouched3 = true;
    }else{
        bTouched3 = false;
    }
    
    //-------------position & Motions--------------
    rotationRawReads = motions.getRotations();
    accelRawReads = motions.getAccelerations();
    accelProcessed = accelRawReads.x*15 + accelRawReads.y*15 + accelRawReads.z*15;
    mRackingSpeed = position.getTravelSpeed();

//-----------get average accelations from Phone sensor----------------------
//    float totalAccl = 0;
//    if (mAvgAccel.size()<=100) {
//        mAvgAccel.push_back(accelProcessed);
//    }else{
//        mAvgAccel.erase(mAvgAccel.begin());
//    }
    
//    for (vector<float>::iterator it = mAvgAccel.begin(); it != mAvgAccel.end(); it++) {
//        totalAccl += *it;
//    }
    
//    float avgAccl = totalAccl / mAvgAccel.size();
//------------------------------end---------------------------------------------------
    
//--------------------MIDI---------------------
    if (bSendNote) {
        midiOut.sendNoteOn(1, notes, 64);
        bSendNote = false;
    }
    int tempX, tempY, tempZ;
    int tempNewX = 0;
    int tempNewY = 0;
    int tempNewZ = 0;
    tempX = tempNewX;
    tempNewX = rotationRawReads.x;
    tempX = 0.7 * tempX + 0.3 * tempNewX;
    tempY = tempNewY;
    tempNewY = rotationRawReads.y;
    tempY = 0.7 * tempY*10 + 0.3 * tempNewY*10;
    tempZ = tempNewZ;
    tempNewZ = rotationRawReads.z;
    tempZ = 0.7 * tempZ + 0.3 * tempNewZ;
    //    tempX = ofMap(tempX, 0, 108, 35, 85);
    //    tempX = ofMap(tempX, 0, 108, 64, 10);
    tempX = ofMap(tempX, 0, 108, 40, 80);
    tempY = ofMap(tempY, 100, 160, 0, 127);
    
    float tempVal, tempNewVal;
    tempVal = 0;
    tempVal = tempNewVal;
    tempNewVal= mRackingSpeed;
    tempVal = 0.7*tempVal + 0.3*tempNewVal;
    
    if(tempVal <=0){
        tempVal = 0;
    }else if (tempVal >= 700){
        tempVal = 700;
    }
    
    cout<<"rake speed: "<<mRackingSpeed<<" processed: "<<tempVal<<std::endl;
    
    
    if (tempVal>0 && tempVal<=300) {
        float trakOneVal = ofMap(tempVal, 0, 300, 0, 127);
        midiOut.sendControlChange(1, 20, trakOneVal);
    }else{
        midiOut.sendControlChange(1, 20, 0);
    }
    
    if(tempVal >250 && tempVal<=500){
        float trackTwoVal = ofMap(tempVal, 250, 500, 0, 127);
        midiOut.sendControlChange(1, 21, trackTwoVal);
    }else{
        midiOut.sendControlChange(1, 21, 0);
    }
    
    if (tempVal>450 && tempVal<=700) {
        float trackThreeVal = ofMap(tempVal, 450, 700, 0, 127);
        midiOut.sendControlChange(1, 22, trackThreeVal);
    }else{
        midiOut.sendControlChange(1, 22, 0);
    }

    midiOut.sendControlChange(1, 23, tempX);
    midiOut.sendControlChange(1, 24, tempY);
    switchRocks();
    playBells();
}

//--------------------------------------------------------------
void ofApp::draw(){
    position.draw();
    if (bTouched1) {
        ofSetColor(255,0 ,0 );
        mRing1.draw();
    }else{
        ofSetColor(255);
        mRing1.draw();
    }
    if (bTouched2) {
        ofSetColor(255,0 ,0 );
        mRing2.draw();
    }else{
        ofSetColor(255);
        mRing2.draw();
    }
    if (bTouched3) {
        ofSetColor(255,0 ,0 );
        mRing3.draw();
    }else{
        ofSetColor(255);
        mRing3.draw();
    }
    
    if (!bHide) {
        mGui.draw();
    }
    
    stringstream text;
    text <<"distance to center "<< distToCenter <<endl<<
    "acceleration raw" << accelRawReads<<endl<<
    "acceleration Processed " << accelProcessedPrev<<endl<<
    "rotation raw" << rotationRawReads<<endl<<
    "rotation processed " << rotationProcessed<<endl<<
    "FPS: " << ofGetFrameRate()<<endl;
    ofDrawBitmapString(text.str(), ofGetWidth()-250, 20);
}


void ofApp::switchRocks(){
    if(bTouched1 != bTouched1Last ){
        if(bTouched1){
            midiOut.sendNoteOn(1, 36);
        }else{
            midiOut.sendNoteOff(1,36);
        }
    }
    
    if(bTouched2 != bTouched2Last){
        if(bTouched2){
            midiOut.sendNoteOn(1, 38);
        }else{
            midiOut.sendNoteOff(1,38);
        }
    }
    
    if(bTouched3 != bTouched3Last){
        if(bTouched3){
            midiOut.sendNoteOn(1, 40);
        }else{
            midiOut.sendNoteOff(1,40);
        }
    }
    
    bTouched1Last = bTouched1;
    bTouched2Last = bTouched2;
    bTouched3Last = bTouched3;
}

void ofApp::playBells(){
    mRakePoint = position.getMidPoint();
    if((mRing1.getCenter() - mRakePoint).length()<40){
        if (!mBell1.isPlaying()) {
            mBell1.setVolume(0.3);
            mBell1.play();
        }
    }
    if((mRing2.getCenter() - mRakePoint).length()<40){
        if (!mBell2.isPlaying()) {
            mBell2.setVolume(0.3);
            mBell2.setSpeed(0.9);
            mBell2.play();
        }
    }
    if((mRing3.getCenter() - mRakePoint).length()<40){
        if (!mBell3.isPlaying()) {
            mBell3.setVolume(0.3);
            mBell3.setSpeed(0.8);
            mBell3.play();
        }
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
        bHide = !bHide;
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
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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