// Refer to the README.md in the example's root folder for more information on usage

#include "line.h"


//--------------------------------------------------------------
void line::setup(){
	INSIDE = 0; // 0000 
	LEFT = 1;   // 0001 
	RIGHT = 2;  // 0010 
	BOTTOM = 4; // 0100 
	TOP = 8;    // 1000 
	x_max = 500; 
	y_max = 600; 
	x_min = 300; 
	y_min = 200; 
	counter = 0;
	ofSetWindowTitle("Line Clipping");
	gui.setup();
    gui.add(xPosition.setup("X", 140, 10, 1000));
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void line::update(){

}

//--------------------------------------------------------------
void line::draw(){
    ofSetColor(255,0,0);
	ofDrawLine(x_min, y_min, x_min, y_max);
	ofDrawLine(x_min, y_min, x_max, y_min);
	ofDrawLine(x_max, y_min, x_max, y_max);
	ofDrawLine(x_max, y_max, x_min, y_max);
	ofDrawLine(xPosition, 0, xPosition, 900);
    clipping(xPosition, 0, xPosition, 900);    
	gui.draw();
}


//--------------------------------------------------------------
void line::keyPressed  (int key){
	
}

//--------------------------------------------------------------
void line::keyReleased  (int key){

}

//--------------------------------------------------------------
void line::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void line::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void line::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void line::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void line::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void line::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void line::windowResized(int w, int h){

}

//--------------------------------------------------------------
void line::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void line::dragEvent(ofDragInfo dragInfo){ 

}

int line::computeCode(float x, float y){
	int code = INSIDE; 
  
    if (x < x_min)       // to the left of rectangle 
        code |= LEFT; 
    else if (x > x_max)  // to the right of rectangle 
        code |= RIGHT; 
    if (y < y_min)       // below the rectangle 
        code |= BOTTOM; 
    else if (y > y_max)  // above the rectangle 
        code |= TOP; 
  
    return code; 
}

void line::clipping(float xInit, float yInit, float xEnd, float yEnd){
	int code1 = computeCode(xInit, yInit); 
    int code2 = computeCode(xEnd, yEnd); 
    //bool accept = false; 
  
    while (true) { 
        if ((code1 == 0) && (code2 == 0)) { 
            ofSetColor(0, 0, 255); 
            ofDrawLine(xInit, yInit, xEnd, yEnd);
            //accept = true; 
            break; 
        } 
        else if (code1 & code2) { 
            break; 
        } else { 
            int code_out; 
            float x, y; 
  
            if (code1 != 0) code_out = code1; 
            else code_out = code2; 

            if (code_out & TOP) { 
                x = xInit + (xEnd - xInit) * (y_max - yInit) / (yEnd - yInit); 
                y = y_max; 
            } else if (code_out & BOTTOM) { 
                x = xInit + (xEnd - xInit) * (y_min - yInit) / (yEnd - yInit); 
                y = y_min; 
            } else if (code_out & RIGHT) { 
                y = yInit + (yEnd - yInit) * (x_max - xInit) / (xEnd - xInit); 
                x = x_max; 
            } else if (code_out & LEFT) { 
                y = yInit + (yEnd - yInit) * (x_min - xInit) / (xEnd - xInit); 
                x = x_min; 
            } 
  
            if (code_out == code1) { 
                xInit = x; 
                yInit = y; 
                code1 = computeCode(xInit, yInit); 
            } else { 
                xEnd = x; 
                yEnd = y; 
                code2 = computeCode(xEnd, yEnd); 
            } 
        } 
    } 
    //if (accept) { 
    //    ofSetColor(0,0,255);
    //    cout <<"Line accepted from " << xInit << ", "
    //         << yInit << " to "<< xEnd << ", " << yEnd << endl; 
    //    // Here the user can add code to display the rectangle 
    //    // along with the accepted (portion of) lines 
    //} else cout << "Line rejected" << endl;
    //ofSetColor(255, 0, 0);
}