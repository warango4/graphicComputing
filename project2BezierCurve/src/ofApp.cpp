// Refer to the README.md in the example's root folder for more information on usage

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Bézier Curve");
	button.addListener(this, &ofApp::buttonPressed);
	gui.setup();
	gui.add(accuracy.setup("t", 5000, 1, 10000));
	gui.add(clearBtn.setup("clear"));
	gui.add(radius.setup("radius", 45, 10, 300));
	gui.add(button.setup("Add Sphere"));
	gui.add(drawLineBtn.setup("Draw Bezier"));
	ofBackground(0, 0, 0);
	mouseIsPressed = false;
	drawLine = false;
	currentPos = 500;

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

	box.set(50);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableDepthTest();
	controlPts.clear();
	bezierPts.clear();

	if (clearBtn) {
		drawLine = false;
		spheres.clear();
		zPosition = 0;
		currentPos = 500;
	}

	for (auto & s : spheres) {
		if (s.inside(ofGetMouseX(), ofGetMouseY()) && mouseIsPressed == true) {
			s.setPosition(ofGetMouseX(), ofGetMouseY(), zPosition);
		}
		s.draw();
	}

	if (drawLineBtn) drawLine = true;

	if (spheres.size() > 1 && drawLine) {
		for (auto & s : spheres) {
			controlPts.push_back(s.getPosition());
		}

		SetupCurve(controlPts, controlPts.size());
		if (bezierPts.size() > 1) {
			ofSetColor(ofColor::red);
			for (unsigned int i = 0; i < controlPts.size() - 1; ++i) {
				ofDrawLine(controlPts[i].x, controlPts[i].y, controlPts[i].z, controlPts[i + 1].x, controlPts[i + 1].y, controlPts[i + 1].z);
			}

			ofSetColor(ofColor::blue);
			for (unsigned int i = 0; i < bezierPts.size(); ++i) {
				ofDrawSphere(bezierPts[i].x, bezierPts[i].y, bezierPts[i].z, 1);
			}

			ofSetColor(ofColor::darkGreen);
			if (currentPos < bezierPts.size() - 1) { 
				box.setPosition(bezierPts[currentPos]);
				box.draw();
				++currentPos;
			} else currentPos = 0;
		}
	}
	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == OF_KEY_UP) {
		zPosition += 10;
	}
	if (key == OF_KEY_DOWN) {
		zPosition -= 10;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	mouseIsPressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	mouseIsPressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::setupCurve(std::vector<ofVec3f> controlPoints, int controlPointsSize) {
	float step = 1.0f / accuracy;

	float u = 0;
	for (int i = 0; i <= accuracy; ++i) {
		bezierPts.push_back(Bezier(u, controlPointsSize - 1, controlPoints));
		u += step;
	}
}

ofVec3f ofApp::bezier(float u, int n, std::vector<ofVec3f> controlPoints) {
	float acumX = 0;
	float acumY = 0;
	float acumZ = 0;
	for (int i = 0; i < n + 1; ++i) {
		float blend = Blending(u, n, i);
		acumX += controlPoints[i].x * blend;
		acumY += controlPoints[i].y * blend;
		acumZ += controlPoints[i].z * blend;
	}
	return ofVec3f(acumX, acumY, acumZ);
}

float ofApp::blending(float u, int n, int k) {
	return Coefficient(n, k) * pow(u, k) * pow(1 - u, n - k);
}

int ofApp::coefficient(int n, int k) {
	return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

int ofApp::factorial(int value) {
	int accum = 1;
	for (int i = 1; i <= value; i++) {
		accum *= i;
	}
	return accum;
}

void ofApp::exit() {
	button.removeListener(this, &ofApp::buttonPressed);
}

void ofApp::buttonPressed() {
	spheres.emplace_back(radius);
}