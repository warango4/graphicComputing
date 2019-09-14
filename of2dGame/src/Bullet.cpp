#include "Bullet.hpp"

void Bullet::setup(bool f_p, ofPoint p, float s) {
    from_player = f_p;
    pos = p;
    speed = s + 3;
    width = 10;
}

void Bullet::update() {
    if (from_player) {
        pos.y -= speed;
    } else {
        pos.y += speed;
    }
}

void Bullet::draw() {
    bresenham(pos.x, pos.y, pos.x, pos.y + 30);
    for (int i = 0; i < nPoints; i++) {
		ofCircle(points[i].x, points[i].y, points[i].z);
	}
}

void Bullet::bresenhamX(int x0, int y0, int x1, int y1, int dx, int dy){
	int i, j, k;

	i = 2 * dy - dx;
	j = 2 * dy;
	k = 2 * (dy - dx);
	if (!(x0 < x1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	nPoints += 1;
	points[nPoints - 1] = ofVec3f(x0, y0, 1);
	while (x0 < x1) {
		if (i < 0)
			i += j;
		else {
			if (y0 < y1)
				++y0;
			else
				--y0;
			i += k;
		}
		++x0;
		points[nPoints - 1] = ofVec3f(x0, y0, 1);
		nPoints += 1;
	}
}

void Bullet::bresenhamY(int x0, int y0, int x1, int y1, int dx, int dy){
	int i, j, k;

	i = 2 * dx - dy;
	j = 2 * dx;
	k = 2 * (dx - dy);
	if (!(y0 < y1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	nPoints += 1;
	points[nPoints - 1] = ofVec3f(x0, y0, 1);
	while (y0 < y1) {
		if (i < 0)
			i += j;
		else {
			if (x0 > x1)
				--x0;
			else
				++x0;
			i += k;
		}
		++y0;
		points[nPoints - 1] = ofVec3f(x0, y0, 1);
		nPoints += 1;
	}
}

void Bullet::bresenham(int x0, int y0, int x1, int y1) {
	nPoints = 0;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		bresenhamX(x0, y0, x1, y1, dx, dy);
	else
		bresenhamY(x0, y0, x1, y1, dx, dy);
}