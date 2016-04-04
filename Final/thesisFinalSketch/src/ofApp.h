#pragma once

#include "ofMain.h"
#include "ring.h"
#include "ofxGui.h"
#include "position.h"
#include "ofxMidi.h"
#include "motions.h"

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
    
    ofxPanel            nGui;
    ofParameter<int>    radius1;
    ofParameter<int>    radius2;
    ofParameter<int>    radius3;
    ofParameter<int>    nearThread;
    ofParameter<int>    farThread;
    ofParameter<int>    tiltAngle;
    ofParameter<ofVec2f>centerPos1;
    ofParameter<ofVec2f>centerPos2;
    ofParameter<ofVec2f>centerPos3;
    
    bool                bHide;
    bool                bTouched1;
    bool                bTouched2;
    bool                bTouched3;
		
    ring                nRing1;
    ring                nRing2;
    ring                nRing3;
    position            position;
    motions             motions;
    ofxMidiOut          midiOut;
    
    float               distToCenter[3];

    ofVec3f             rotationReads;
    ofVec3f             accelReads;
    
};
