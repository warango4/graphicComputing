#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char **argv){
    //glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}