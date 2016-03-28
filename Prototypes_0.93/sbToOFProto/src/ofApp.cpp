#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    rotationRead.set(0,0,0);
    accelRead.set(0, 0, 0);
    host = "localhost";
    name = "of_listener";
    description = "subscrible motion data to of";
    sb.addSubscribe("OF_read_rotate_alpha", Spacebrew::TYPE_RANGE);
    sb.addSubscribe("OF_read_rotate_beta", Spacebrew::TYPE_RANGE);
    sb.addSubscribe("OF_read_rotate_gamma", Spacebrew::TYPE_RANGE);
    sb.addSubscribe("OF_read_accel_x", Spacebrew::TYPE_RANGE);
    sb.addSubscribe("OF_read_accel_y", Spacebrew::TYPE_RANGE);
    sb.addSubscribe("OF_read_accel_z", Spacebrew::TYPE_RANGE);

    sb.connect(host, name, description);
    Spacebrew::addListener(this, sb);


}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
//    cout<< "rotate read: "<< rotationRead <<std::endl;
//    cout<< "accel read: "<< accelRead <<std::endl;
    ofSetColor(0);
    stringstream text;
    text<< "Rotat read from SB: " << rotationRead<<endl<<
    "Accel read from SB: " << accelRead <<endl;
    ofDrawBitmapString(text.str(), 20, 20);
    
}


//_____________________________________________________________
void ofApp::onMessage(Spacebrew::Message & m){
    if (m.name == "OF_read_rotate_alpha") {
        rotationRead.x = m.valueRange();
    }else if(m.name == "OF_read_rotate_beta"){
        rotationRead.y = m.valueRange();
    }else if(m.name == "OF_read_rotate_gamma"){
        rotationRead.z = m.valueRange();
    }else if(m.name == "OF_read_accel_x"){
        accelRead.x = m.valueRange();
    }else if(m.name == "OF_read_accel_y"){
        accelRead.y = m.valueRange();
    }else if(m.name == "OF_read_accel_z"){
        accelRead.z = m.valueRange();
    }

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
