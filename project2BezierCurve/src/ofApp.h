#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include <math.h> 
#include "ofxGui.h"
#include "customSphere.h"

using namespace std;

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void buttonPressed();
	void exit();
	void setupCurve(std::vector<ofVec3f> controlPoints, int controlPointsSize);
	ofVec3f bezier(float u, int n, std::vector<ofVec3f> controlPoints);
	float blending(float u, int n, int k);
	int coefficient(int n, int k);
	int factorial(int value);

	ofxIntSlider accuracy;
	ofxButton clearBtn;
	ofxPanel gui;
	ofxFloatSlider radius;
	ofxFloatSlider zPos;
	ofxButton button;
	ofxButton drawLineBtn;
	ofBoxPrimitive box;

	std::list<CustomSphere> spheres;
	std::vector<ofVec3f> controlPts;
	std::vector<ofVec3f> bezierPts;

	bool mouseIsPressed;
	bool drawLine;
	int zPosition;
	int currentPos;
};