
#pragma once

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

#include "ofMain.h"

class Player {
public:
    ofPoint pos;
    ofPoint scaler;
    float width, height, speed, h, w;
    int lives;
    float scale = 10;
    
    bool is_left_pressed, is_right_pressed, is_down_pressed, is_up_pressed, rotate, bigger, smaller;
    

    void setup(float width1, float height1, ofPoint _pos);
    void update();
    void draw();
    void shoot();
    
    void calculate_movement();
    
    bool check_canshoot();

	int nRotation;
};


#endif /* Player_hpp */
