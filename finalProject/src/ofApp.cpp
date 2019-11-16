// Refer to the README.md in the example's root folder for more information on usage

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofSetWindowTitle("Final Project");
	ofBackground(0, 0, 0);
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	
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
	
	currentPos = 500;
	
	ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
}

//--------------------------------------------------------------
void ofApp::update() {
	pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);

    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
    );
}

//--------------------------------------------------------------
void ofApp::draw() {
	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);

	ofEnableDepthTest();

	cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
	cam.begin();

	ofEnableLighting();
	pointLight.enable();
	pointLight2.enable();
	pointLight3.enable();

	if (clearBtn) {
		spheres.clear();
		boxes.clear();
		cones.clear();
		currentPos = 500;
	}

	cam.end();

	for (auto & s : spheres) {
		if (s.inside(ofGetMouseX(), ofGetMouseY()) && mouseIsPressed == true) {
			s.setPosition(ofGetMouseX(), ofGetMouseY(), zPosition);
		}

		if (rotateSpheres) {
			s.rotateDeg(spinX, 1.0, 0.0, 0.0);
			s.rotateDeg(spinY, 0, 1.0, 0.0);
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

		if (rotateCones) {
			c.rotateDeg(spinX, 1.0, 0.0, 0.0);
			c.rotateDeg(spinY, 0, 1.0, 0.0);
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

		if (rotateBoxes) {
			b.rotateDeg(spinX, 1.0, 0.0, 0.0);
			b.rotateDeg(spinY, 0, 1.0, 0.0);
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
	case 'l':
		bDrawLights = !bDrawLights;
		break;
	case '1':
		rotateBoxes = !rotateBoxes;
		break;
	case '2':
		rotateCones = !rotateCones;
		break;
	case '3':
		rotateSpheres = !rotateSpheres;
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

void ofApp::exit() {
	addSphere.removeListener(this, &ofApp::addSpherePressed);
	addCone.removeListener(this, &ofApp::addConePressed);
	addBox.removeListener(this, &ofApp::addBoxPressed);
}

void ofApp::addSpherePressed() {
	spheres.emplace_back(radius);
}

void ofApp::addBoxPressed() {
	boxes.emplace_back(height, width, depth);
}

void ofApp::addConePressed(){
	cones.emplace_back(radius, height);
}