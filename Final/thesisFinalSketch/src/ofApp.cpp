#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(255);
    bHide = false;
    bTouched1 = false;
    bTouched2 = false;
    bTouched3 = false;
    
    nGui.setup("rings");
    nGui.add(radius1.set("Ring1 Radius ", 300, 0, 500));
    nGui.add(radius2.set("Ring2 Radius ", 150, 0, 500));
    nGui.add(radius3.set("Ring3 Radius ", 80, 0, 500));
    nGui.add(nearThread.set("Near Threashold", 240, 0, 255));
    nGui.add(farThread.set("Far Threashold", 230, 0, 255));
    nGui.add(tiltAngle.set("Tile angle", 0, 0, 30));

    nGui.add(centerPos1.set("Ring1 Center ", ofVec2f(ofGetWidth(), ofGetHeight()/2), ofVec2f(0,0), ofVec2f(ofGetWidth(), ofGetHeight())));
    nGui.add(centerPos2.set("Ring2 Center ", ofVec2f(ofGetWidth()/2, ofGetHeight()/2), ofVec2f(0,0), ofVec2f(ofGetWidth(), ofGetHeight())));
    nGui.add(centerPos3.set("Ring3 Center ", ofVec2f(ofGetWidth()/2, ofGetHeight()/2), ofVec2f(0,0), ofVec2f(ofGetWidth(), ofGetHeight())));
    
    nRing1.setup(centerPos1, radius1);
    nRing2.setup(centerPos2, radius2);
    nRing3.setup(centerPos3, radius3);
    position.setup();
    distToCenter[3];
    for (int i = 0; i < 3; i++) {
        distToCenter[i] = 0;
    }
    
    //-------midi----------
    midiOut.listPorts(); // via instance
    midiOut.openVirtualPort("Thesis MIDI");
    
    //--------motions----------
    motions.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    nRing1.update(centerPos1, radius1);
    nRing2.update(centerPos2, radius2);
    nRing3.update(centerPos3, radius3);
    
    position.update(nearThread, farThread, tiltAngle);
    distToCenter[0] = position.getIntersectDist(centerPos1);
    distToCenter[1]= position.getIntersectDist(centerPos2);
    distToCenter[2]= position.getIntersectDist(centerPos3);

    if (distToCenter[0] <= radius1) {
        bTouched1 = true;
    }else{
        bTouched1 = false;
    }
    
    if (distToCenter[1] <= radius2) {
        bTouched2 = true;
    }else{
        bTouched2 = false;
    }
    
    if (distToCenter[2] <= radius3) {
        bTouched3 = true;
    }else{
        bTouched3 = false;
    }
    
    //-------------Motions--------------
    rotationReads = motions.getRotations();
    accelReads = motions.getAccelerations();
    cout<<"rotationreads: "<<rotationReads<<std::endl;
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    position.draw();
    
    if (bTouched1) {
        int midiMsg = ofMap(distToCenter[0], radius1,0, 0, 127);
        midiOut.sendControlChange(1, 20, midiMsg);
        ofSetColor(255,0 ,0 );
        nRing1.draw();
    }else{
        midiOut.sendControlChange(1, 20, 0);
        ofSetColor(255);
        nRing1.draw();
    }
    if (bTouched2) {
        int midiMsg = ofMap(distToCenter[1], radius2,0, 0, 127);
        midiOut.sendControlChange(1, 21, midiMsg);
        ofSetColor(255,0 ,0 );
        nRing2.draw();
    }else{
        midiOut.sendControlChange(1, 21, 0);
        ofSetColor(255);
        nRing2.draw();
    }
    if (bTouched3) {
        int midiMsg = ofMap(distToCenter[2], radius3,0, 0, 127);
        midiOut.sendControlChange(1, 22, midiMsg);
        ofSetColor(255,0 ,0 );
        nRing3.draw();
    }else{
        midiOut.sendControlChange(1, 22, 0);
        ofSetColor(255);
        nRing3.draw();
    }
    
    if (!bHide) {
        nGui.draw();
    }
    
    stringstream text;
    text <<"distance to center: "<< distToCenter<<endl;
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
