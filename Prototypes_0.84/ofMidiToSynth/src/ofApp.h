#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxGui.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxMidiOut midiOut;
    int channel, control;
    int lastNote, velocity;
    
    ofParameter<int>notes;
    ofParameter<int> knob1;
    ofParameter<int> knob2;
    ofParameter<bool> bSendNote;
    ofxPanel gui;
    
		
};
