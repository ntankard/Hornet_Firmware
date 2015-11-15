#include "Point.h"
#include "CONFIG.h"

Point::Point()
{
	_angle = 0;
	_distance = 0;
	_coorX = 0;
	_coorY = 0;
	_coorX_S = 0;
	_coorY_S = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Point::setPolar(float angle, float distance)
{
	_angle = angle;
	_distance = distance;
	_coorX = distance * cos(angle * PI / 180);
	_coorY = distance * sin(angle * PI / 180);
	_coorX_S = distance * cos((angle + 45) * PI / 180);
	_coorY_S = distance * sin((angle + 45) * PI / 180);
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

float Point::getX(int i) const  //returns a copy of _coorX
{
	if (i == 0)
	{
		return _coorX;
	}
	return _coorX_S;
}

//-----------------------------------------------------------------------------------------------------------------------------

float Point::getY(int i) const  //returns a copy of coorY
{
	if (i == 0)
	{
		return _coorY;
	}
	return _coorY_S;
}
