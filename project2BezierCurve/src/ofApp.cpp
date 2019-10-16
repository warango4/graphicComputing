// Refer to the README.md in the example's root folder for more information on usage

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Bézier Curve");
    button.addListener(this, &ofApp::buttonPressed);
	gui.setup();
    gui.add(accuracy.setup("t", 5000, 1, 10000));
    //gui.add(drawBtn.setup("draw"));
    gui.add(clearBtn.setup("clear"));
    gui.add(radius.setup("radius", 140, 10, 300));
	gui.add(button.setup("Add Sphere"));
    gui.add(drawLineBtn.setup("Draw Bezier"));
    ofBackground(0, 0, 0);
	mouseIsPressed = false;

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(clearBtn) spheres.clear();
    int x = 0;
	for (auto & s : spheres) {
		//s.setPosition(200 * (x + 1), 200, 0);
		//if(i == 0) s.setPosition(200 * (x + 1), 200, 0);
		++x;
		if(s.inside(ofGetMouseX(), ofGetMouseY()) && mouseIsPressed == true) {
			s.setPosition(ofGetMouseX(), ofGetMouseY(), 0);
		}
		s.draw();
	}

	if(spheres.size() > 1 && drawLineBtn) {
		for(auto & s : spheres){
			controlPts.push_back(s.getPosition());
		}
		std::vector<ofVec3f> end = bezier_curve(controlPts, accuracy);
		if(end.size() > 1) {
            ofSetColor(ofColor::red);
            for(unsigned int i = 0; i < controlPts.size() - 1; ++i){
                ofDrawLine(controlPts[i].x, controlPts[i].y, controlPts[i + 1].x, controlPts[i + 1].y);
            }
            ofSetColor(ofColor::blue);
            for(unsigned int i = 0; i < end.size(); ++i) {
                //if(i == 0) cout << end.size() << endl;
                //cout << end[i].x << " " << end[i].y << endl;
                //path.circle(end[i].x, end[i].y, 0.1);
                //path.draw();
                ofDrawSphere(end[i].x, end[i].y, end[i].z, 1);
            }
        }
	}
    gui.draw();    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouseIsPressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mouseIsPressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

float ofApp::interpolate(float pos1, float pos2, float accur){
    //return pos1 + ((pos1 - pos2) * accur);
    return (1 - accur) * pos1 + accur * pos2;
}

std::vector<ofVec3f> ofApp::bezier_curve(std::vector<ofVec3f>& anchor, float accur){
    if(anchor.size() <= 2) return anchor;

    std::vector<ofVec3f> end;
    //end.push_back(anchor.front());

    for(float i = 0.f; i < accur; ++i){
        float t = i / accur;

        std::vector<ofVec3f> temp(anchor);

        while(temp.size() > 1){
            std::vector<ofVec3f> temp2;
            for (unsigned int j = 1; j < temp.size(); ++j)
                temp2.push_back(ofVec3f(interpolate(temp[j-1].x, temp[j].x, t),
                                        interpolate(temp[j-1].y, temp[j].y, t),
										0));
            temp.swap(temp2);
        }

        end.push_back(temp.front());
    }

    return end;
}

void ofApp::exit() {
	button.removeListener(this, &ofApp::buttonPressed);
}

void ofApp::buttonPressed() {
	//++j;
	spheres.emplace_back(radius);
}