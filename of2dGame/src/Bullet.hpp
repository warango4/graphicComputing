
#pragma once

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>

#include "ofMain.h"

class Bullet {
public:
    ofPoint pos;
    float speed;
    float width;
    bool from_player;
    
    void setup(bool f_p, ofPoint p, float s);
    void update();
    void draw();

    void bresenhamX(int x0, int y0, int x1, int y1, int dx, int dy);
    void bresenhamY(int x0, int y0, int x1, int y1, int dx, int dy);
    void bresenham(int x0, int y0, int x1, int y1);
    
    int nPoints = 0;
    ofVec3f points[1000];
};

#endif /* Bullet_hpp */
