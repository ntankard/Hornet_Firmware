#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Feature.h"

test(Feature_Setup)
{
	Feature f1;
	assertEqual(f1.getState(), FEATURE_NULL);
	assertEqual(f1.getEnterStartX(), 0);
	assertEqual(f1.getEnterStartY(), 0);
	assertEqual(f1.getEnterEndX(), 0);
	assertEqual(f1.getEnterEndY(), 0);
	assertEqual(f1.getExitStartX(), 0);
	assertEqual(f1.getExitStartY(), 0);
	assertEqual(f1.getExitEndX(), 0);
	assertEqual(f1.getExitEndY(), 0);
	assertEqual(f1.getLife(), 0);
	assertEqual(f1.getOccurances(), 0);
}

test(Feature_Set)
{
	Feature f1;
	Pattern pattern;
	Pattern pattern2;
	Point point;
	Point point2;
	point.setXY(1, 2);
	point2.setXY(3, 4);
	pattern.setPattern(&point, &point2);
	point.setXY(5, 6);
	point2.setXY(7, 8);
	pattern2.setPattern(&point, &point2);
	f1.setFeature(&pattern, &pattern2);
	assertEqual(f1.getState(), FEATURE_DATA);
	assertEqual(f1.getEnterStartX(), 1);
	assertEqual(f1.getEnterStartY(), 2);
	assertEqual(f1.getEnterEndX(), 3);
	assertEqual(f1.getEnterEndY(), 4);
	assertEqual(f1.getExitStartX(), 5);
	assertEqual(f1.getExitStartY(), 6);
	assertEqual(f1.getExitEndX(), 7);
	assertEqual(f1.getExitEndY(), 8);
	assertEqual(f1.getLife(), L_FEATURE_LIFE);
	assertEqual(f1.getOccurances(), 0);
}

test(Feature_updateOccurances)
{
	Feature f1;
	f1.updateOccurances();
	assertEqual(f1.getOccurances(), 1);
}

test(Feature_LoseLife)
{
	Feature f1;
	Pattern pattern;
	Pattern pattern2;
	Point point;
	Point point2;
	point.setXY(1, 2);
	point2.setXY(3, 4);
	pattern.setPattern(&point, &point2);
	point.setXY(5, 6);
	point2.setXY(7, 8);
	pattern2.setPattern(&point, &point2);
	f1.setFeature(&pattern, &pattern2);
	f1.loseLife();
	assertEqual(f1.getLife(), L_FEATURE_LIFE-1);
}
#endif