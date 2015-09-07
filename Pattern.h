#pragma once 
#include "Arduino.h"
#include "math.h"

class Pattern
{
public:

	Pattern(Point* start, Point* end)
	{
		_start_coorX = start->getX();
		_start_coorY = start->getY();
		_end_coorX = end->getX();
		_end_coorY = end->getY();

		_angle = atan((_end_coorY - _start_coorY) / (_end_coorX - _start_coorX)) * 180 / PI;
	}

	float getAngle() const //returns a copy of _angle
	{
		return _angle;
	}

private:
	float _angle;
	float _start_coorX;
	float _start_coorY;
	float _end_coorX;
	float _end_coorY;
};