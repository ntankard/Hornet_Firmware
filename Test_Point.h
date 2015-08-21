#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Error.h"
#include "Point.h"

test(Point_)
{
	Error e;
	Point point(100, 30);

	//Check point is made correctly
	assertEqaul(point.getDistance, 30);
	assertEqaul(point.getAngle, 30);
	assertEqual(point.getX, 87);
	assertEqual(point.getY, 50);
}

#endif;
