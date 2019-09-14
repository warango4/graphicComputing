
#pragma once

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>

#include "ofMain.h"

class Enemy {
public:
    ofPoint pos;
    float speed;
    float amplitude;
    float width;
    float height;
    
    float start_shoot;
    float shoot_interval;
    
    void setup(float max_enemy_amplitude, float max_enemy_shoot_interval);
    void update();
    void draw();
    bool time_to_shoot();
    
    int backnforth;
    float deltaX;
};

#endif /* Enemy_hpp */
