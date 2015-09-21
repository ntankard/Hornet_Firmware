#pragma once 
#include "Arduino.h"
#include "math.h"
#include "Point.h"

enum DataState { NOT_SET, SET };

class Pattern
{
public:

	Pattern(DataState state)
	{
		_state = state;
		_start_coorX = 0;
		_start_coorY = 0;
		_end_coorX = 0;
		_end_coorY = 0;
		_angle = 0;
	}

	void setPattern(Point* start, Point* end)
	{
		_start_coorX = start->getX();
		_start_coorY = start->getY();
		_end_coorX = end->getX();
		_end_coorY = end->getY();
		_angle = atan((_end_coorY - _start_coorY) / (_end_coorX - _start_coorX)) * 180 / PI;
	}

	void setPattern(Point* start, Point* end, DataState state)
	{
		_state = state;
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

	float getStartCoordX()
	{
		return _start_coorX;
	}

	float getStartCoordY()
	{
		return _start_coorY;
	}

	float getEndCoordX()
	{
		return _end_coorX;
	}

	float getEndCoordY()
	{
		return _end_coorY;
	}

	DataState getState()
	{
		return _state;
	}

	void setState(DataState state)
	{
		_state = state;
	}

private:
	DataState _state;
	float _angle;
	float _start_coorX;
	float _start_coorY;
	float _end_coorX;
	float _end_coorY;
};