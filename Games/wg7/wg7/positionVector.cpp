#include "stdafx.h"
#include "positionVector.h"

positionVector::positionVector()
{
	this->x = 0;
	this->y = 0;
}
positionVector::positionVector(double X, double Y)
{
	this->x = X;
	this->y = Y;
}
positionVector::~positionVector()
{

}


void positionVector::normalize()
{
	double Magnitude = this->magnitude();
	this->x /= Magnitude;
	this->y /= Magnitude;
}

void positionVector::add(double dx, double dy) {
	this->x += dx;
	this->y += dy;
}

void positionVector::multiply(double mx, double my) {
	this->x *= mx;
	this->y *= my;
}

double positionVector::magnitude() {
	return pow(pow(this->x, 2) + pow(this->y, 2), 0.5);
}

void positionVector::disposeVector() {
	delete this;
}

positionVector* positionVector::subtract(positionVector* v2, positionVector* v1) {
	return  new positionVector(v2->x - v1->x, v2->y - v1->y);
}

double positionVector::getDistance(positionVector a, positionVector b)
{
	return (pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5));
}

double positionVector::getDistance( positionVector* b)
{
	return (pow(pow(this->x - b->x, 2) + pow(this->y - b->y, 2), 0.5));
}

double positionVector::getLength(double x1, double y1, double x2, double y2)
{
	return (pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5));

}
