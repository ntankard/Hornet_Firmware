#pragma once 
#include "Arduino.h"
#include "math.h"

class Point
{
public:

	Point();
	void setPolar(float angle, float distance);

	float getAngle() const;
	float getDistance() const;
	float getX() const;
	float getY() const;
	
private:

	float _angle;
	float _distance;
	float _coorX;
	float _coorY;
};