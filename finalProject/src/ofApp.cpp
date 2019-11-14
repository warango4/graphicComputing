// Refer to the README.md in the example's root folder for more information on usage

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetWindowTitle("Bézier Curve");
	addSphere.addListener(this, &ofApp::addSpherePressed);
	addCone.addListener(this, &ofApp::addConePressed);
	addBox.addListener(this, &ofApp::addBoxPressed);
	gui.setup();
	gui.add(clearBtn.setup("clear"));
	gui.add(addSphere.setup("Add Sphere"));
	gui.add(addCone.setup("Add Cone"));
	gui.add(addBox.setup("Add box"));
	gui.add(radius.setup("radius", 45, 10, 300));
	gui.add(height.setup("height", 45, 10, 300));
	gui.add(width.setup("width", 45, 10, 300));
	gui.add(depth.setup("depth", 45, 10, 300));
	ofBackground(0, 0, 0);
	//drawLine = false;
	currentPos = 500;
	cam.setDistance(160);

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

	//box.set(50);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableDepthTest();
	cam.begin();
	if (clearBtn) {
		spheres.clear();
		boxes.clear();
		cones.clear();
		currentPos = 500;
	}

	for (auto & s : spheres) {
		if (s.inside(ofGetMouseX(), ofGetMouseY()) && mouseIsPressed == true) {
			s.setPosition(ofGetMouseX(), ofGetMouseY(), zPosition);
		}
		if (drawSphereWireframe) {
			ofNoFill();
			ofSetColor(0, 0, 255);
			s.drawWireframe();
			continue;
		}
		s.draw();
	}

	for (auto & c : cones) {
		if (c.inside(ofGetMouseX(), ofGetMouseY()) && mouseIsPressed == true) {
			c.setPosition(ofGetMouseX(), ofGetMouseY(), zPosition);
		}
		if (drawConeWireframe) {
			ofNoFill();
			ofSetColor(0, 255, 0);
			c.setScale(1.01f);
			c.drawWireframe();
			c.setScale(1.f);
			continue;
		}
		c.draw();
	}

	for (auto & b : boxes) {
		if (b.inside(ofGetMouseX(), ofGetMouseY()) && mouseIsPressed == true) {
			b.setPosition(ofGetMouseX(), ofGetMouseY(), zPosition);
		}
		if (drawBoxWireframe) {
			ofNoFill();
			ofSetColor(255, 0, 0);
			b.setScale(1.01f);
			b.drawWireframe();
			b.setScale(1.f);
			continue;
		}
		b.draw();
	}

	cam.end();
	ofDisableDepthTest();

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'b':
		drawBoxWireframe = !drawBoxWireframe;
		break;
	case 'c':
		drawConeWireframe = !drawConeWireframe;
		break;
	case 's':
		drawSphereWireframe = !drawSphereWireframe;
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
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

/**void ofApp::SetupCurve(std::vector<ofVec3f> controlPoints, int controlPointsSize) {
	float step = 1.0f / accuracy;

	float u = 0;
	for (int i = 0; i <= accuracy; ++i) {
		bezierPts.push_back(Bezier(u, controlPointsSize - 1, controlPoints));
		u += step;
	}
}

ofVec3f ofApp::Bezier(float u, int n, std::vector<ofVec3f> controlPoints) {
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

float ofApp::Blending(float u, int n, int k) {
	return Coefficient(n, k) * pow(u, k) * pow(1 - u, n - k);
}

int ofApp::Coefficient(int n, int k) {
	return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

int ofApp::Factorial(int value) {
	int accum = 1;
	for (int i = 1; i <= value; i++) {
		accum *= i;
	}
	return accum;
}**/

void ofApp::exit() {
	addSphere.removeListener(this, &ofApp::addSpherePressed);
	addCone.removeListener(this, &ofApp::addConePressed);
	addBox.removeListener(this, &ofApp::addBoxPressed);
}

void ofApp::addSpherePressed() {
	//++j;
	spheres.emplace_back(radius);
}

void ofApp::addBoxPressed() {
	boxes.emplace_back(height, width, depth);
}

void ofApp::addConePressed(){
	cones.emplace_back(radius, height);
}