#pragma once
#include "ObjectWEvents.h"

class CustomCone: public ofConePrimitive, public ObjectWEvents {
public:
	CustomCone():CustomCone(20, 20){}

	CustomCone(float radius, float height) {
		//this->set(radius);
		RegisterMouseEvents();
		this->hasRadius = true;
        ObjectWEvents::setRadius(radius);
		ofConePrimitive::setRadius(radius);
        ofConePrimitive::setHeight(height);
		RegisterMouseEvents();
        this->setPosition(200, 600, 0);
        //this->z = 0;
		GetInfo();
	}

	~CustomCone() {
		UnregisterMouseEvents();
	}

	void GetInfo();
	// Inherited via GenericObjectWithEvents
	virtual void draw(int x = 0, int y = 0, int z = 0, int w = 0, int h = 0, int screenW = 0, int screenH = 0) override;
};