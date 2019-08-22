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
	//ofBackground(255,255,255);
	ofSetWindowTitle("graphics example");
	ofSetColor(255,0,0);
	//ofDrawLine(x_min, y_min, x_min, y_max);
	//ofDrawLine(x_min, y_min, x_max, y_min);
	//ofDrawLine(x_max, y_min, x_max, y_max);
	//ofDrawLine(x_max, y_max, x_min, y_max);
	gui.setup();
    gui.add(xPosition.setup("X", 140, 10, 300));
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	//xPosition = ofSystemTextBoxDialog("Enter x position", "");
}

//--------------------------------------------------------------
void line::update(){
	// update event slowly increments the counter variable
	//counter = counter + 0.033f;
}

//--------------------------------------------------------------
void line::draw(){
	//---------------------------  transparency
	//ofSetHexColor(0x00FF33);
	//ofDrawRectangle(400,350,100,100);
	//// alpha is usually turned off - for speed puposes.  let's turn it on!
	//ofEnableAlphaBlending();
	//ofSetColor(255,0,0,127);   // red, 50% transparent
	//ofDrawRectangle(450,430,100,33);
	//ofSetColor(255,0,0,(int)(counter * 10.0f) % 255);   // red, variable transparent
	ofDrawLine(x_min, y_min, x_min, y_max);
	ofDrawLine(x_min, y_min, x_max, y_min);
	ofDrawLine(x_max, y_min, x_max, y_max);
	ofDrawLine(x_max, y_max, x_min, y_max);
	clipping(105, 170, 280, 180);
	ofDrawLine(105, 170, 280, 180);

	//ofDisableAlphaBlending();
	//ofSetHexColor(0x000000);
	//ofDrawBitmapString("transparency", 410,500);

	//ofDrawRectangle(10,10,-100, 80, 80);
	//cout << xPosition << endl;
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
  
    // Initialize line as outside the rectangular window 
    bool accept = false; 
  
    while (true) { 
        if ((code1 == 0) && (code2 == 0)) { 
            // If both endpoints lie within rectangle 
            accept = true; 
            break; 
        } 
        else if (code1 & code2) { 
            // If both endpoints are outside rectangle, 
            // in same region 
            break; 
        } else { 
            // Some segment of line lies within the 
            // rectangle 
            int code_out; 
            float x, y; 
  
            // At least one endpoint is outside the  
            // rectangle, pick it. 
            if (code1 != 0) code_out = code1; 
            else code_out = code2; 
  
            // Find intersection point; 
            // using formulas y = yInit + slope * (x - xInit), 
            // x = xInit + (1 / slope) * (y - yInit) 
            if (code_out & TOP) { 
                // point is above the clip rectangle 
                x = xInit + (xEnd - xInit) * (y_max - yInit) / (yEnd - yInit); 
                y = y_max; 
            } else if (code_out & BOTTOM) { 
                // point is below the rectangle 
                x = xInit + (xEnd - xInit) * (y_min - yInit) / (yEnd - yInit); 
                y = y_min; 
            } else if (code_out & RIGHT) { 
                // point is to the right of rectangle 
                y = yInit + (yEnd - yInit) * (x_max - xInit) / (xEnd - xInit); 
                x = x_max; 
            } else if (code_out & LEFT) { 
                // point is to the left of rectangle 
                y = yInit + (yEnd - yInit) * (x_min - xInit) / (xEnd - xInit); 
                x = x_min; 
            } 
  
            // Now intersection point x,y is found 
            // We replace point outside rectangle 
            // by intersection point 
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
    if (accept) { 
        cout <<"Line accepted from " << xInit << ", "
             << yInit << " to "<< xEnd << ", " << yEnd << endl; 
        // Here the user can add code to display the rectangle 
        // along with the accepted (portion of) lines 
    } else cout << "Line rejected" << endl;
}