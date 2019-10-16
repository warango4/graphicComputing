#include "objectWEvents.h"

// the static event, or any static variable, must be initialized outside of the class definition.
ofEvent<ofVec2f> ObjectWEvents::clickedGlobal = ofEvent<ofVec2f>();

ObjectWEvents::~ObjectWEvents(){
	UnregisterMouseEvents();
}

void ObjectWEvents::RegisterMouseEvents(){
	ofRegisterMouseEvents(this); // this will enable our class to listen to the mouse events.
	withEvents = true;
}

void ObjectWEvents::UnregisterMouseEvents(){
	if (withEvents)	{
		ofUnregisterMouseEvents(this); // disable listening to mouse events.
		withEvents = false;
	}
}

void ObjectWEvents::setWithHoverEffect(bool value){
	withHoverEffect = value;
}

void ObjectWEvents::setColor(ofColor color) {
	myColor = color;
	tempColor = color;
}

void ObjectWEvents::setHoverColor(ofColor color){
	hoverColor = color;
}

void ObjectWEvents::setRadius(float radius){
	this->radius = radius;
	setHasRadius(true);
}

void ObjectWEvents::setHasRadius(bool value){
	hasRadius = value;
}

void ObjectWEvents::mouseDragged(ofMouseEventArgs & mouse){}

void ObjectWEvents::mousePressed(ofMouseEventArgs & mouse){}

bool ObjectWEvents::inside(float _x, float _y){
	if (hasRadius) {
		return (ofVec2f(_x, _y).distance(ofVec2f(x, y)) < radius);
	}
	else {
		return ((_x > x) && (_x < x + width) && (_y > y) && (_y < y + height));
	}
}

void ObjectWEvents::mouseMoved(ofMouseEventArgs & mouse) {
	if (inside(mouse.x, mouse.y)) {
		// if the mouse is hovered the object an event will be notified (broadcasted) 
		// the Event object will contain the mouse position, so this values are accesible to any class that is listening.
		ofVec2f mousePos = ofVec2f(mouse.x, mouse.y);
		ofNotifyEvent(hovered, mousePos, this);
		isHovered = true;
		if (withHoverEffect){
			myColor = hoverColor;
		}
	} else {
		if (isHovered) {
			if (!inside(mouse.x, mouse.y)) {
				ofVec2f mousePos = ofVec2f(mouse.x, mouse.y);
				ofNotifyEvent(hovered, mousePos, this);
				isHovered = false;
				if (withHoverEffect) {
					myColor = tempColor;
				}
			}
		}
	}
}

void ObjectWEvents::mouseReleased(ofMouseEventArgs & args) {
	if (inside(args.x, args.y))	{
		// if the mouse is pressed over the object an event will be notified (broadcasted) 
		// the Event object will contain the mouse position, so this values are accesible to any class that is listening.
		ofVec2f mousePos = ofVec2f(args.x, args.y);
		ofNotifyEvent(clickedInside, mousePos, this);
		ofNotifyEvent(clickedGlobal, mousePos);
		++this->clicks;
		if (this->clicks == 2) {
			this->clicks = 0;
		}
	}
}

void ObjectWEvents::mouseScrolled(ofMouseEventArgs & args){}

void ObjectWEvents::mouseEntered(ofMouseEventArgs & args){}

void ObjectWEvents::mouseExited(ofMouseEventArgs & args){}
