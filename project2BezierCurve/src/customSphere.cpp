#include "customSphere.h"


void CustomSphere::draw(int x, int y, int z, int w, int h, int screenW, int screenH) {
	ofSetColor(this->myColor);
	auto currentPos = this->getPosition();
	this->x = currentPos.x;
	this->y = currentPos.y;
	this->z = currentPos.z;
	ofSpherePrimitive::draw();
}