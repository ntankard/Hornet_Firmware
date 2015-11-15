#pragma once 
//#include "Arduino.h"
#include "math.h"

class Point
{
public:

	Point();
	void setPolar(float angle, float distance);

	float getAngle() const;
	float getDistance() const;

	float getX(int i = 0) const;
	float getY(int i = 0) const;
	//float getX_S() const;
	//float getY_S() const;
	
private:

	float _angle;
	float _distance;
	float _coorX;
	float _coorY;
	float _coorX_S;
	float _coorY_S;

};