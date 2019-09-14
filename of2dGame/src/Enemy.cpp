
#include "Enemy.hpp"

void Enemy::setup(float max_enemy_amplitude, float max_enemy_shoot_interval) {
    width = 30;
    height = 30;
	if (ofRandom(2)>1){
		pos.x = ofRandom(ofGetWidth());
		pos.y = 200;
	} else {
		pos.x = ofRandom(ofGetWidth());
		pos.y = 600;
	}

    speed = 2.5;
    amplitude = ofRandom(max_enemy_amplitude);
    shoot_interval = ofRandom(1, max_enemy_shoot_interval);
    start_shoot = ofGetElapsedTimef();
    backnforth = 0;
}

void Enemy::update() {
    pos.y += amplitude * cos(ofGetElapsedTimef());
    pos.x += amplitude * sin(ofGetElapsedTimef());
}

void Enemy::draw() {
    ofPath path;
    path.setFillColor(ofColor::blue);
    ofFill();
    path.rectangle(pos.x - width/2, pos.y - height/2, width, height);
    path.draw();
}

bool Enemy::time_to_shoot() {
    if (ofGetElapsedTimef() - start_shoot > shoot_interval) {
        start_shoot = ofGetElapsedTimef();
        return true;
    }
    return false;
}
