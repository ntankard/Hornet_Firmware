#include "Point.h"

Point::Point()
{
	_angle = 0;
	_distance = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Point::setPolar(float angle, float distance)
{
	_angle = angle;
	_distance = distance;
	_coorX = distance * cos(angle * PI / 180);
	_coorY = distance * sin(angle * PI / 180);
}

//-----------------------------------------------------------------------------------------------------------------------------

float Point::getAngle() const //returns a copy of _angle
{
	return _angle;
}

//-----------------------------------------------------------------------------------------------------------------------------

float Point::getDistance() const  //returns a copy of _distance
{
	return _distance;
}

//-----------------------------------------------------------------------------------------------------------------------------

float Point::getX() const  //returns a copy of _coorX
{
	return _coorX;
}

//-----------------------------------------------------------------------------------------------------------------------------

float Point::getY() const  //returns a copy of coorY
{
	return _coorY;
}