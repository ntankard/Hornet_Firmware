#pragma once

#include "Point.h"

class Line
{
public:
	Line();
	void setPoints(Point start, Point end);
	double getAngle();
	Point getStart(){ return _start; }
	Point getEnd(){ return _end; }
private:
	Point _start;
	Point _end;
	double _angle;
};

