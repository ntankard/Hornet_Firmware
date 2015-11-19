#include "CollisionAvoidance.h"
#include <Arduino.h>
#include "CONFIG.h"


CollisionAvoidance::CollisionAvoidance()
{
	_xComp = 0;
	_yComp = 0;
	_minDistance = LA_SAFTEY_RADIUS;

	_CompensatorRegister.getData()[0] = 50;
	_CompensatorRegister.getData()[1] = 50;
}

//-----------------------------------------------------------------------------------------------------------------------------

void CollisionAvoidance::newPoint(double angle, double distance)
{
	if (distance < LA_SAFTEY_RADIUS)
	{
		double adjustedAngle = ((angle) + 180.0) * (PI / 180.0);
		double adjustedDistance = LA_SAFTEY_RADIUS - distance;

		double x = -(adjustedDistance * sin(adjustedAngle));
		double y = -(adjustedDistance * cos(adjustedAngle));

		_xComp += x;
		_yComp += y;

		if (adjustedDistance > _minDistance)
		{
			_minDistance = adjustedDistance;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void CollisionAvoidance::endOfSweep()
{
	// were there any points in the radius?	
	if (_minDistance != LA_MIN_RADIUS)
	{
		double angle = (atan2(_yComp, _xComp));// + (PI);
		double per = 100.0 * ((_minDistance) / (LA_SAFTEY_RADIUS - LA_MIN_RADIUS));

		if (angle > (2.0 * PI))
		{
			angle = angle - (2.0*PI);
		}
		if (_xComp >= 0)
		{
			angle = (PI / 2.0) - angle;
		}
		else if ( _yComp >=0)
		{
			angle = -(angle - (PI / 2.0));
		}
		else
		{
			angle = -(PI / 2.0 + (PI + angle));
		}

		_CompensatorRegister.getData()[0] = ((per * sin(angle)) / 4) + 50;
		_CompensatorRegister.getData()[1] = ((per * cos(angle)) / 4) + 50;

		_xComp = 0;
		_yComp = 0;
		_minDistance = LA_MIN_RADIUS;
	}
	else
	{
		_CompensatorRegister.getData()[0] = 50;
		_CompensatorRegister.getData()[1] = 50;
	}
}