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
    
    ofxPanel            mGui;
    ofParameterGroup    mParameters;
    ofParameter<int>    nearThread;
    ofParameter<int>    farThread;
    ofParameter<int>    tiltAngle;
    ofParameter<bool>   bSendNote;
    ofParameter<int>    notes;
    
    bool                bHide;
    bool                bTouched1;
    bool                bTouched2;
    bool                bTouched3;
		
    ring                mRing1, mRing2, mRing3;
    position            position;
    motions             motions;
    ofxMidiOut          midiOut;
    float               distToCenter[3];
    ofVec3f             rotationRawReads;
    ofVec3f             accelRawReads;
    int                 rotationProcessedPrev;
    int                 rotationProcessed;
    int                 accelProcessedPrev;
    int                 accelProcessed;
    
};
