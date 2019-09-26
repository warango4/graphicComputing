#include "bezier.h"


//--------------------------------------------------------------
void bezier::setup(){
	ofSetWindowTitle("Bézier Curve");
    ctrlPtsSize = 0;
    drawPressed = false;
	gui.setup();
    gui.add(accuracy.setup("t", 5000, 1, 10000));
    gui.add(drawBtn.setup("draw"));
    gui.add(clearBtn.setup("clear"));
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void bezier::update(){
    
}

//--------------------------------------------------------------
void bezier::draw(){
    if(clearBtn) {
        drawPressed = false;
        controlPts.clear();
    }

    if(drawBtn) drawPressed = true;

    if(drawPressed){
        std::vector<ofVec2f> end = bezier_curve(controlPts, accuracy);
        if(end.size() > 1) {
            ofSetColor(ofColor::red);
            for(unsigned int i = 0; i < controlPts.size() - 1; ++i){
                ofDrawLine(controlPts[i].x, controlPts[i].y, controlPts[i + 1].x, controlPts[i + 1].y);
            }
            ofSetColor(ofColor::blue);
            for(unsigned int i = 0; i < end.size(); ++i) {
                ofCircle(end[i].x, end[i].y, 1);
            }
        }        
    }
	gui.draw();
}


//--------------------------------------------------------------
void bezier::keyPressed(int key){
	
}

//--------------------------------------------------------------
void bezier::keyReleased(int key){

}

//--------------------------------------------------------------
void bezier::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void bezier::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void bezier::mousePressed(int x, int y, int button){
    controlPts.push_back(ofVec2f(x, y));
}

//--------------------------------------------------------------
void bezier::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void bezier::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void bezier::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void bezier::windowResized(int w, int h){

}

//--------------------------------------------------------------
void bezier::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void bezier::dragEvent(ofDragInfo dragInfo){ 

}

float bezier::interpolate(float pos1, float pos2, float accur){
    return (1 - accur) * pos1 + accur * pos2;
}

std::vector<ofVec2f> bezier::bezier_curve(std::vector<ofVec2f>& anchor, float accur){
    if(anchor.size() <= 2) return anchor;

    std::vector<ofVec2f> end;
    //end.push_back(anchor.front());

    for(float i = 0.f; i < accur; ++i){
        float t = i / accur;

        std::vector<ofVec2f> temp(anchor);

        while(temp.size() > 1){
            std::vector<ofVec2f> temp2;
            for (unsigned int j = 1; j < temp.size(); ++j)
                temp2.push_back(ofVec2f(interpolate(temp[j-1].x, temp[j].x, t),
                                        interpolate(temp[j-1].y, temp[j].y, t)));
            temp.swap(temp2);
        }

        end.push_back(temp.front());
    }

    return end;
}
