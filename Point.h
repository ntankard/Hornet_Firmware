#pragma once 

class Point
{
public:

	Point(float angle, float distance) 
	{
		_angle = angle;
		_distance = distance;
	}

	float getAngle()
	{
		return _angle;
	}

	float getDistance()
	{
		return _distance;
	}

private:

	float _angle;
	float _distance;
};