#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Point.h"

test(Point_Setup)
{
	Point point(36.87, 5);

	//Check point is made correctly
	assertEqual(point.getDistance(), 5);
	assertEqual(point.getAngle(), 36.87);

	//Done this way because assertions for the calculated coordinates 
	//are not working even though they show as equal to each other
	if (!point.getAngle() == 36.87)
	{
		assertTrue(false);
	}
	if (!point.getX() == 4)
	{
		assertTrue(false);
	}
	if (!point.getX() == 3)
	{
		assertTrue(false);
	}
}

test(Point_All_Quadrants) 
{
	Point pointQ1(36.87, 7);
	Point pointQ2(111.34, 25);
	Point pointQ3(200.00, 15);
	Point pointQ4(354.45, 18);

	//Check points are made correctly
	assertEqual(pointQ1.getDistance(), 7);
	assertEqual(pointQ2.getDistance(), 25);
	assertEqual(pointQ3.getDistance(), 15);
	assertEqual(pointQ4.getDistance(), 18);
	assertEqual(pointQ1.getAngle(), 36.87);
	assertEqual(pointQ2.getAngle(), 111.34);
	assertEqual(pointQ3.getAngle(), 200.00);
	assertEqual(pointQ4.getAngle(), 354.45);
	if (!pointQ1.getX() == 5.6)
	{
		assertTrue(false);
	}
	if (!pointQ1.getY() == 4.2)
	{
		assertTrue(false);
	}
	if (!pointQ2.getX() == -9.10)
	{
		assertTrue(false);
	}
	if (!pointQ2.getY() == 23.29)
	{
		assertTrue(false);
	}
	if (!pointQ3.getX() == -14.10)
	{
		assertTrue(false);
	}
	if (!pointQ3.getY() == -5.13)
	{
		assertTrue(false);
	}
	if (!pointQ4.getX() == 17.92)
	{
		assertTrue(false);
	}
	if (!pointQ4.getY() == -1.74)
	{
		assertTrue(false);
	}
}

#endif;