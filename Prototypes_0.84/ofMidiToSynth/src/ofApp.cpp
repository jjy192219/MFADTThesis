#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    midiOut.listPorts(); // via instance
    
    midiOut.openVirtualPort("OFMIDI");
    
    channel = 1;
    control = 1;
    velocity = 64;
    lastNote = 36;
    
    //-------------------GUI--------------
    
    gui.setup("MIDI");
    gui.add(bSendNote.set("send note",false));
    gui.add(notes.set("note val", 36, 0, 127));
    gui.add(knob1.set("knob1", 0, 0, 127));
    gui.add(knob2.set("knob2", 0, 0, 127));

}

//--------------------------------------------------------------
void ofApp::update(){
    if (bSendNote) {
        midiOut.sendNoteOn(channel, notes, velocity);
        bSendNote = false;
    }else{
//        midiOut.sendNoteOff(channel, notes);
    }
    
    midiOut.sendControlChange(1, 50, knob1);
    midiOut.sendControlChange(1, 51, knob2);

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    gui.draw();
    stringstream text;
    text << "connect to port "<<midiOut.getPort()
    <<"\"" << midiOut.getName() << "\"" <<endl
    <<"note: " << notes <<endl
    <<"velocity: " << velocity <<endl;
    ofDrawBitmapString(text.str(), ofGetWidth()-250, 20);
    
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
//    midiOut.sendNoteOn(channel, notes, velocity);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    midiOut.sendNoteOff(channel, notes);

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
