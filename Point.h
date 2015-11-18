#pragma once 
//#include "Arduino.h"
#include "math.h"

class Point
{
public:

	Point();
	void setPolar(double angle, double distance);

	double getAngle() const;
	double getDistance() const;

	double getX(int i = 0) const;
	double getY(int i = 0) const;
	//double getX_S() const;
	//double getY_S() const;
	
private:

	double _angle;
	double _distance;
	double _coorX;
	double _coorY;
	double _coorX_S;
	double _coorY_S;

};