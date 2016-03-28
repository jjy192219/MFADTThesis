#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    accelRead = 0;
    host = "localhost";
    name = "of_listener";
    description = "subscrible motion data to of";
    sb.addSubscribe("accelListener", Spacebrew::TYPE_RANGE);
    sb.connect(host, name, description);

}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::onMessage(Spacebrew::Message & m){
    if (m.name == "accelListener") {
        accelRead = m.valueRange();
//        accelRead = ofToInt(m.value);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    stringstream text;
    text<< "read received from SB: " << accelRead<<endl;
    ofDrawBitmapString(text, 20, 20);

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
