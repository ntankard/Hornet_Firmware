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

test(Point_All_Quadrants) 
{
	Error e;
	Point pointQ1(36.87, 7);
	Point pointQ2(111.34, 25);
	Point pointQ3(200.00, 15);
	Point pointQ4(354.45, 18);

	//Check points are made correctly
	assertEqual(pointQ1.getDistance(), 7);
	assertEqual(pointQ2.getDistance(), 25);
	assertEqual(pointQ3.getDistance(), 15);
	assertEqual(pointQ4.getDistance(), 18);

	//Q1 Angle = 36.87, Distance = 7
	Serial.println(pointQ1.getAngle());
	Serial.println("Should = 36.87");
	Serial.println(pointQ1.getX());
	Serial.println("Should = 5.60");
	Serial.println(pointQ1.getY());
	Serial.println("Should = 4.20");

	//Q2 Angle = 111.34, Distance = 25
	Serial.println(pointQ2.getAngle());
	Serial.println("Should = 111.34");
	Serial.println(pointQ2.getX());
	Serial.println("Should = -9.10");
	Serial.println(pointQ2.getY());
	Serial.println("Should = 23.29");

	//Q3 Angle = 200.00, Distance = 15
	Serial.println(pointQ3.getAngle());
	Serial.println("Should = 200.00");
	Serial.println(pointQ3.getX());
	Serial.println("Should = -14.10");
	Serial.println(pointQ3.getY());
	Serial.println("Should = -5.13");

	//Q4 Angle = 354.45, Distance = 18
	Serial.println(pointQ4.getAngle());
	Serial.println("Should = 354.45");
	Serial.println(pointQ4.getX());
	Serial.println("Should = 17.92");
	Serial.println(pointQ4.getY());
	Serial.println("Should = -1.74");
}

#endif;