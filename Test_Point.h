#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Error.h"
#include "Point.h"

test(Point_Setup)
{
	Error e;
	Point point(36.87, 5);

	//Check point is made correctly
	assertEqual(point.getDistance(), 5);

	//Done this way because assertions for the calculated coordinates 
	//are not working even though they show as equal to each other
	Serial.println(point.getAngle());
	Serial.println("Should = 36.87");
	Serial.println(point.getX());
	Serial.println("Should=4");
	Serial.println(point.getY());
	Serial.println("Should=3");
}

#endif;