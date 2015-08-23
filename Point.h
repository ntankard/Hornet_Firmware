#pragma once 
#include "Arduino.h"

class Point
{
public:

	Point(float angle, float distance) 
	{
		_angle = angle;
		_distance = distance;
	}

	const float getAngle() const //returns a copy of _angle
	{
		return _angle;
	}

	const float getDistance() const  //returns a copy of _distance
	{
		return _distance;
	}

private:

	float _angle;
	float _distance;
};