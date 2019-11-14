#include "CustomBox.h"

void CustomBox::GetInfo() {
	auto currentPos = this->getPosition();
	this->x = currentPos.x;
	this->y = currentPos.y;
    this->z = currentPos.z;
	this->width = this->getWidth();
	this->height = this->getHeight();
}

void CustomBox::draw(int x, int y, int z, int w, int h, int screenW, int screenH) {
	GetInfo();
	ofSetColor(this->myColor);
	ofBoxPrimitive::draw();
}