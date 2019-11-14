#include "CustomCone.h"

void CustomCone::GetInfo() {
	auto currentPos = this->getPosition();
	this->x = currentPos.x;
	this->y = currentPos.y;
    this->z = currentPos.z;
	//this->height = this->getHeight();
}

void CustomCone::draw(int x, int y, int z, int w, int h, int screenW, int screenH) {
	GetInfo();
	ofSetColor(this->myColor);
	ofConePrimitive::draw();
}