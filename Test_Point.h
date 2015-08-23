#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Error.h"
#include "Point.h"

test(Point_Setup)
{
	Error e;
	Point point(100, 30);

	//Check point is made correctly
	assertEqual(point.getDistance(), 30);
	assertEqual(point.getAngle(), 100);
	//assertEqual(point.getX, 87);
	//assertEqual(point.getY, 50);
}

#endif;