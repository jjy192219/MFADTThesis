//
//  motions.cpp
//  thesisFinalSketch
//
//  Created by Eric Jiang on 4/4/16.
//
//

#include "motions.h"

motions::motions(){
    
}

void motions::setup(){

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
    raking.load("Crackle.wav");
    raking.setMultiPlay(true);
}

void motions::onMessage(Spacebrew::Message & m){
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

ofVec3f motions::getRotations(){
    return rotationRead;
}

ofVec3f motions::getAccelerations(){
    return accelRead;
}

void motions::playRake(int accel){
    if (!raking.getIsPlaying()) {
        float control = ofMap(accel, 140, 210, 0, 1);
        raking.setSpeed(control);
        raking.setVolume(0.2);
        raking.play();
    }
}

void motions::stopPlayRake(){
        raking.stop();
}