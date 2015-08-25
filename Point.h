#pragma once 
#include "Arduino.h"
#include "math.h"

class Point
{
public:

	Point(float angle, float distance) 
	{
		_angle = angle;
		_distance = distance;
		_coorX = distance * cos(angle * PI / 180);
		_coorY = distance * sin(angle * PI / 180);
	}

	const float getAngle() const //returns a copy of _angle
	{
		return _angle;
	}

	const float getDistance() const  //returns a copy of _distance
	{
		return _distance;
	}

	const float getX() const  //returns a copy of _coorX
	{
		return _coorX;
	}

	const float getY() const  //returns a copy of coorY
	{
		return _coorY;
	}

private:

	float _angle;
	float _distance;
	float _coorX;
	float _coorY;
};