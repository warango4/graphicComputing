//#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include <math.h> 
using namespace std;

#include "ofMain.h"

class line : public ofBaseApp{
	
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

		int computeCode(float x, float y);
		void clipping(float xInit, float yInit, float xEnd, float yEnd);

		int counter;
		bool bSmooth;
		//string xPosition;
		int INSIDE; // 0000 
		int LEFT;   // 0001 
		int RIGHT;  // 0010 
		int BOTTOM; // 0100 
		int TOP;    // 1000 
		int x_max; 
		int y_max; 
		int x_min; 
		int y_min; 

		ofxIntSlider xPosition;
		ofxPanel gui;
};