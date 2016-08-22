#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bJunkRead = false;
    ofEnableSmoothing();
    ofSetCircleResolution(48);
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
    
    float tempVal, tempNewVal;
    tempVal = 0;
    tempVal = tempNewVal;
    tempNewVal= mRackingSpeed;
    if (tempNewVal-tempVal >=1000) {
        tempNewVal=tempVal;
        bJunkRead = true;
        cout<<"<<<<<<<<<junk read filtered>>>>>>>>>"<<std::endl;
    }else{
        bJunkRead = false;
    }
    tempVal = 0.7*tempVal + 0.3*tempNewVal;

    if(tempVal <=0){
        tempVal = 0;
    }else if (tempVal >= 700){
        tempVal = 700;
    }
    
//    cout<<"rake speed: "<<mRackingSpeed<<" processed: "<<tempVal<<std::endl;
    cout<<"bHide: "<<bHide<<std::endl;
    
    
    if (tempVal>0 && tempVal<=150) {
        float trakOneVal = ofMap(tempVal, 0, 150, 0, 127);
        midiOut.sendControlChange(1, 20, trakOneVal);
    }else{
        midiOut.sendControlChange(1, 20, 0);
    }
    
    if(tempVal >100 && tempVal<=350){
        float trackTwoVal = ofMap(tempVal, 100, 350, 0, 127);
        midiOut.sendControlChange(1, 21, trackTwoVal);
    }else{
        midiOut.sendControlChange(1, 21, 0);
    }
    
    if (tempVal>300 && tempVal<=700) {
        float trackThreeVal = ofMap(tempVal,300, 700, 0, 127);
        midiOut.sendControlChange(1, 22, trackThreeVal);
    }else{
        midiOut.sendControlChange(1, 22, 0);
    }
    switchRocks();
    playBells();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(!bHide){
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
        
        mGui.draw();
        
        stringstream text;
        text <<"distance to center "<< distToCenter <<endl<<
        "acceleration raw" << accelRawReads<<endl<<
        "acceleration Processed " << accelProcessedPrev<<endl<<
        "rotation raw" << rotationRawReads<<endl<<
        "rotation processed " << rotationProcessed<<endl<<
        "FPS: " << ofGetFrameRate()<<endl;
        ofDrawBitmapString(text.str(), ofGetWidth()-250, 20);
    
    }
    
    if(!bJunkRead){
        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(0.4);
        if(bDrawRippleOne){
            if (mRippleOne<= ofGetWidth()/3) {
                ofDrawCircle(mRing1.getCenter(), mRippleOne);
                mRippleOne += 3;
            }else{
                mRippleOne = 0;
            }
        }else{
            mRippleOne = 0;
        }
        
//        checkRipples();
//        if (bFinishRippleOne) {
//            float temp = mRippleOne;
//            mRippleOne= 0;
//            if (temp<= ofGetWidth()/3) {
//                ofDrawCircle(mRing1.getCenter(), temp);
//            }else{
//                temp = 0;
//                bFinishRippleOne = false;
//            }
//        }
        if(bDrawRippleTwo){
            if (mRippleTwo <= ofGetWidth()/3) {
                ofDrawCircle(mRing2.getCenter(), mRippleTwo);
                mRippleTwo += 3;
            }else{
                mRippleTwo = 0;
            }
        }else{
            mRippleTwo = 0;
        }
        if(bDrawRippleThree){
            if (mRippleThree <= ofGetWidth()/3) {
                ofDrawCircle(mRing3.getCenter(), mRippleThree);
                mRippleThree += 3;
            }else{
                mRippleThree = 0;
            }
        }else{
            mRippleThree = 0;
        }
    }
    
    ofSetColor(255);
    ofNoFill();
    ofSetLineWidth(1.0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

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
    if((mRing1.getCenter() - mRakePoint).length()<60){
        if (!mBell1.isPlaying()) {
            mBell1.setVolume(0.3);
            mBell1.play();
        }else{
            bDrawRippleOne = true;
        }
    }else{
        bDrawRippleOne = false;
    }
    if((mRing2.getCenter() - mRakePoint).length()<60){
        if (!mBell2.isPlaying()) {
            mBell2.setVolume(0.3);
            mBell2.setSpeed(0.9);
            mBell2.play();
        }else{
            bDrawRippleTwo = true;
        }
    }else{

        bDrawRippleTwo = false;
    }
    if((mRing3.getCenter() - mRakePoint).length()<60){
        if (!mBell3.isPlaying()) {
            mBell3.setVolume(0.3);
            mBell3.setSpeed(0.8);
            mBell3.play();
        }else{
            bDrawRippleThree = true;
        }
    }else{
        bDrawRippleThree = false;
    }
}

//void ofApp::checkRipples(){
//    if (bDrawRippleOne!= bDrawRippleOneLast) {
//        if (bDrawRippleOne) {
//            if (mRippleOne <= ofGetWidth()/3) {
//                mRippleOne += 3;
//                ofDrawCircle(mRing1.getCenter(), mRippleOne);
//            }else{
//                mRippleOne = 0;
//            }
//        }else{
//            bFinishRippleOne = true;
//        }
//    }
//    
//    bDrawRippleOneLast = bDrawRippleOne;
//}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == '1' ){
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