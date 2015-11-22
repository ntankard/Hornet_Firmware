#pragma once

#include "Point.h"

/**
* \class	Line
*
* \brief	A representation of a straight line in the lidar data
*/
class Line
{
public:
	Line();
	void setPoints(Point start, Point end);

	double getAngle();
	Point getStart(){ return _start; }
	Point getEnd(){ return _end; }
private:

	/** \brief	The first point in the line */
	Point _start;

	/** \brief	The last point in the line */
	Point _end;

	/** \brief	The angle of the line relative to the Y axis */
	double _angle;
};

