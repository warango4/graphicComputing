#pragma once
#include "ofMain.h"

class ObjectWEvents {
    protected:
    	bool withEvents;
    	bool isBeingDragged;
    	bool isHovered;
    	bool withHoverEffect;
    	uint8_t clicks;

    	ofColor myColor;
    	ofColor tempColor;
    	ofColor hoverColor;
    	int x;
    	int y;
		int z;
    	int height;
    	int width;
    	bool hasRadius;
    	float radius;
        
    public:
    	static ofEvent<ofVec2f> clickedGlobal;
    	ofEvent<ofVec2f> clickedInside;
    	ofEvent<ofVec2f> hovered;
    	ofEvent<ofVec2f> exited;
    	ObjectWEvents() {
    		clicks = 0;
    		isHovered = false;
    		isBeingDragged = false;
    		withEvents = false;
    		withHoverEffect = true;
    		myColor = ofColor::white;
    		tempColor = myColor;
    		hoverColor = ofColor::lightGreen;
    		hasRadius = false;
    		radius = 0;
    	}
    	virtual ~ObjectWEvents();

    	void RegisterMouseEvents();
    	void UnregisterMouseEvents();
    	void setWithHoverEffect(bool value);
    	void setColor(ofColor color);
    	void setHoverColor(ofColor color);
    	void setRadius(float radius);
    	void setHasRadius(bool value);
    	virtual void draw(int x = 0, int y = 0, int z = 0, int w = 0, int h = 0, int screenW = 0, int screenH = 0) = 0;
    	virtual void mouseDragged(ofMouseEventArgs & mouse);
    	virtual void mousePressed(ofMouseEventArgs & mouse);
    	virtual void mouseMoved(ofMouseEventArgs & mouse);
    	virtual void mouseReleased(ofMouseEventArgs & args);
    	virtual void mouseScrolled(ofMouseEventArgs & args);
    	virtual void mouseEntered(ofMouseEventArgs & args);
    	virtual void mouseExited(ofMouseEventArgs & args);
    	virtual bool inside(float _x, float _y);
};