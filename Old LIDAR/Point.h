#pragma once 
#include "Arduino.h"
#include "math.h"

enum PointState { HEAD, TAIL, NULLPOINT, DATA };

class Point
{
public:

	//Point();
	//void setPolar(float angle, float distance);

	Point()
	{
		_angle = 0;
		_distance = 0;
		_state = NULLPOINT;
	}

	Point(float angle, float distance) 
	{
		_angle = angle;
		_distance = distance;
		_coorX = distance * cos(angle * PI / 180);
		_coorY = distance * sin(angle * PI / 180);
	}

	Point(PointState state)
	{
		_angle = 0;
		_distance = 0;
		_state = state;
	}

	void setPoint(float angle, float distance)
	{
		_angle = angle;
		_distance = distance;
		_coorX = distance * cos(angle * PI / 180);
		_coorY = distance * sin(angle * PI / 180);
	}

	void setPoint(float angle, float distance, PointState state)
	{
		_angle = angle;
		_distance = distance;
		_coorX = distance * cos(angle * PI / 180);
		_coorY = distance * sin(angle * PI / 180);
		_state = state;
	}

	void setXY(float x, float y)
	{
		_coorX = x;
		_coorY = y;
	}

	void setState(PointState state)
	{
		_state = state;
	}

	PointState getState() const
	{
		return _state;
	}

	float getAngle() const //returns a copy of _angle
	{
		return _angle;
	}

	float getDistance() const  //returns a copy of _distance
	{
		return _distance;
	}

	float getX() const  //returns a copy of _coorX
	{
		return _coorX;
	}

	float getY() const  //returns a copy of coorY
	{
		return _coorY;
	}
	
private:
	PointState _state;
	float _angle;
	float _distance;
	float _coorX;
	float _coorY;
};