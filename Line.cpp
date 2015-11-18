#include "Line.h"


#include "CONFIG.h"
Line::Line()
{
}

void Line::setPoints(Point start, Point end)
{
	_end = end;
	_start = start;

	_angle = atan2(end.getX(0) - start.getX(0), end.getY(0) - start.getY(0)) * (180.0 / PI);
}

double Line::getAngle()
{
	return _angle;
}