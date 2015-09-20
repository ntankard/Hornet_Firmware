#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Feature.h"
#include "Point.h"
#include "Pattern.h"
#include "LidarNavigation.h"

//90 degrees
test(isFeature_Corner)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(i, 10);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(L_POINTS_IN_PATTERN, 10 + i);
		iter2++;
	}
	d->createPattern();
	assertTrue(l->isFeature(l->getPattern(), d->getPattern()));
}

//90 degrees
test(isFeature_OnRangeBounds_X)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(i + 1, 10);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(L_POINTS_IN_PATTERN + L_PATTERN_RANGE_IN_FEATURE, 10 + i);
		iter2++;
	}
	d->createPattern();
	assertTrue(l->isFeature(l->getPattern(), d->getPattern()));
}

//90 degrees
test(isFeature_OutsideRangeBounds_X)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(i + 1, 10);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(L_POINTS_IN_PATTERN + L_PATTERN_RANGE_IN_FEATURE + 1, 10 + i);
		iter2++;
	}
	d->createPattern();
	assertFalse(l->isFeature(l->getPattern(), d->getPattern()));
}

//90 degrees
test(isFeature_OnRangeBounds_Y)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(10, i+1);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(10 + i, L_POINTS_IN_PATTERN + L_PATTERN_RANGE_IN_FEATURE);
		iter2++;
	}
	d->createPattern();
	assertTrue(l->isFeature(l->getPattern(), d->getPattern()));
}

//90 degrees
test(isFeature_OutsideRangeBounds_Y)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(10, i + 1);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(10 + i, L_POINTS_IN_PATTERN + L_PATTERN_RANGE_IN_FEATURE + 1);
		iter2++;
	}
	d->createPattern();
	assertFalse(l->isFeature(l->getPattern(), d->getPattern()));
}

//45 degrees
test(isFeature_45DegreeCorner_ShouldFail)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(i, 10);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(L_POINTS_IN_PATTERN + i, 10 + i);
		iter2++;
	}
	d->createPattern();
	assertFalse(l->isFeature(l->getPattern(), d->getPattern()));
}

//86.19 degrees
test(isFeature_imperfectCorner)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(i , 10);
		iter++;
	}
	l->createPattern();
	LidarNavigation* d = new LidarNavigation();
	PointNode* node2 = d->getHead();
	DoublyLinkedNodeIterator<Point> iter2 = DoublyLinkedNodeIterator<Point>(*node2);
	iter2++;
	for (float i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter2.getNode()->getValue().setXY(L_POINTS_IN_PATTERN + (i/15), 10 + i);
		iter2++;
	}
	d->createPattern();
	Serial.println(d->getPattern()->getAngle());
	assertTrue(l->isFeature(l->getPattern(), d->getPattern()));
}

#endif