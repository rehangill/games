#pragma once

#include<conio.h>
#include<math.h>
class positionVector
{
public:
	double x;
	double y;
	void normalize();
	void add(double dx, double dy);
	void multiply(double mx, double my);
	positionVector();
	positionVector(double X, double Y);
	~positionVector();
	double magnitude();
	void disposeVector();
	static positionVector* subtract(positionVector * v2, positionVector * v1);
	static double getDistance(positionVector a, positionVector b);
	double getDistance(positionVector * b);
	
	static double getLength(double x1, double y1, double x2, double y2);
};

