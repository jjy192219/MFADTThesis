//
//  motions.cpp
//  finalSketchIRLed
//
//  Created by Eric Jiang on 4/28/16.
//
//

#include "motions.h"

motions::motions(){
    
}

void motions::setup(){
//    mRotationRead.set(0,0,0);
//    mAccelRead.set(0, 0, 0);
    mSerial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = mSerial.getDeviceList();
    int baud = 115200;
    mSerial.setup(1, baud);

}

void motions::update(){
    if (mSerial.available()) {
        unsigned char bytesReturned[33];
        memset(bytesReturned,0,10);
        mSerial.readBytes(bytesReturned, 33);
        string serialData = (char*) bytesReturned;
        cout<<"serialData: " <<serialData <<std::endl;
        mSerial.flush();
    }
}