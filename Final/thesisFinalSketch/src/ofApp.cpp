#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    mGui.add(nearThread.set("Near Threashold", 181, 0, 255));
    mGui.add(farThread.set("Far Threashold", 161, 0, 255));
    mGui.add(tiltAngle.set("Tile angle", 0, 0, 30));

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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    position.update(nearThread, farThread, tiltAngle);
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
    
    //--------------MIDI--------------
    if (bSendNote) {
        midiOut.sendNoteOn(1, notes, 64);
        bSendNote = false;
    }
    
    //-------------Motions--------------
    rotationRawReads = motions.getRotations();
    accelRawReads = motions.getAccelerations();

    int tempX, tempY;
    int tempNewX = 0;
    int tempNewY = 0;
    tempX = tempNewX;
    tempNewX = rotationRawReads.x;
    tempX = 0.7 * tempX + 0.3 * tempNewX;
    
    tempY = tempNewY;
    tempNewY = rotationRawReads.y;
    tempY = 0.7 * tempY*10 + 0.3 * tempNewY*10;
    
    tempX = ofMap(tempX, 0, 108, 0, 127);
    tempY = ofMap(tempY, 100, 200, 0, 127);
    
    midiOut.sendControlChange(1, 23, tempX);
    midiOut.sendControlChange(1, 24, tempY);

    cout<<"tempX: "<<tempX<<" tempY: "<<tempY<<std::endl;


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    position.draw();
    
    if (bTouched1) {
        int midiMsg = ofMap(distToCenter[0], mRing1.getSize(),0, 0, 127);
        midiOut.sendControlChange(1, 20, midiMsg);
        ofSetColor(255,0 ,0 );
        mRing1.draw();
    }else{
        midiOut.sendControlChange(1, 20, 0);
        ofSetColor(255);
        mRing1.draw();
    }
    if (bTouched2) {
        int midiMsg = ofMap(distToCenter[1], mRing2.getSize(),0, 0, 127);
        midiOut.sendControlChange(1, 21, midiMsg);
        ofSetColor(255,0 ,0 );
        mRing2.draw();
    }else{
        midiOut.sendControlChange(1, 21, 0);
        ofSetColor(255);
        mRing2.draw();
    }
    if (bTouched3) {
        int midiMsg = ofMap(distToCenter[2], mRing3.getSize(),0, 0, 127);
        midiOut.sendControlChange(1, 22, midiMsg);
        ofSetColor(255,0 ,0 );
        mRing3.draw();
    }else{
        midiOut.sendControlChange(1, 22, 0);
        ofSetColor(255);
        mRing3.draw();
    }
    
    if (!bHide) {
        mGui.draw();
    }
    
    stringstream text;
    text <<"distance to center "<< distToCenter <<endl<<
    "acceleration raw" << accelRawReads<<endl<<
    "acceleration Processed " << accelProcessed<<endl<<
    "rotation raw" << rotationRawReads<<endl<<
    "rotation processed " << rotationProcessed<<endl;
    ofDrawBitmapString(text.str(), ofGetWidth()-250, 20);
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
