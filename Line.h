#pragma once

#include "Point.h"

class Line
{
public:
	Line();
	void setPoints(Point start, Point end);
	float getAngle();
private:
	Point _start;
	Point _end;
	float _angle;
};

