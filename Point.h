#pragma once

class Point
{
public:
	Point(float angle, float distance) 
	{ 
		_angle = angle;
		_distance = distance;
	}

private:
	float _angle;
	float _distance;
};