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

	float interpolate(float x, float y, float accur);
	std::vector<ofVec3f> bezier_curve(std::vector<ofVec3f>& anchor, float accur);
	void buttonPressed();
	void onMouseIn(ofVec2f & e);
	void exit();
	void SetupCurve(std::vector<ofVec3f> controlPoints, int controlPointsSize);
	ofVec3f Bezier(float u, int n, std::vector<ofVec3f> controlPoints);
	float Blending(float u, int n, int k);
	int Coefficient(int n, int k);
	int Factorial(int value);

	ofxIntSlider accuracy;
	ofxButton clearBtn;
	ofxPanel gui;
	ofxFloatSlider radius;
	ofxFloatSlider zPos;
	ofxButton button;
	ofxButton drawLineBtn;
	std::list<CustomSphere> spheres;
	std::vector<ofVec3f> controlPts;
	std::vector<ofVec3f> bezierPts;
	bool mouseIsPressed;
	bool upPressed;
	bool downPressed;
	int zPosition;
	ofBoxPrimitive box;
	int currentPos;
	bool drawLine;
	//int j = 0;
	//int i = 100;
	//int k = 150;
};