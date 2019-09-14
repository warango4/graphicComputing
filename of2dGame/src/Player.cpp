
#include "Player.hpp"
#include "ofApp.hpp"

//--------------------------------------------------------------
void Player::setup(float width1, float height1, ofPoint _pos){
    height = height1;
    width = width1;
    pos.set(_pos);
    speed = 2.8;
    lives = 7;
    scaler.x = 2;
    scaler.y = 2;
    nRotation = 0;
}

//--------------------------------------------------------------
void Player::update(){
    if (is_up_pressed)
        pos.y -= speed;
    if (is_down_pressed)
        pos.y += speed;
    if (is_left_pressed)
        pos.x -= speed;
    if (is_right_pressed)
        pos.x += speed;
	h = height;
	w = width; 
}

//--------------------------------------------------------------
void Player::draw(){       
    ofRectangle _rect(pos.x - width/2, pos.y - height/2, w, h);  
    if(bigger){
        _rect.scaleFromCenter(scaler.x, scaler.y);
    } 
    if(smaller){
        _rect.scaleFromCenter(-0.5, -0.5);
    }
    if(rotate){
        ofPushMatrix();
        ofPoint center = _rect.getCenter();
        ofTranslate(center);  
        if(nRotation == 1) ofRotateZDeg(50);
        if(nRotation == 2) ofRotateZDeg(-120);
        if(nRotation == 3) ofRotateZDeg(-40);
        if(nRotation == 4) {
            ofRotateZDeg(220);
            nRotation = 0;
        }
        ofRect(0, 0, w, h);
        ofPopMatrix();
    } else {
        ofFill();
        ofDrawRectangle(_rect); 
    }
}

//--------------------------------------------------------------
void Player::shoot(){
}
