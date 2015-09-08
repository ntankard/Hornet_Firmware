#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Error.h"
#include "Point.h"

test(isPattern_DeadStraightLine)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(((i + 1) * 10), 10);
		iter++;
	}
	assertTrue(l->isPattern());
}

test(isPattern_StraightLineMinorDeviation)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + 2);
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertTrue(l->isPattern());
}

test(isPattern_NoiseyLine_ShouldFail)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + 5);
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertFalse(l->isPattern());
}

test(isPattern_SlightCurve_ShouldPass)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + i/5);
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertTrue(l->isPattern());
}

test(isPattern_HeavyCurve_ShouldFail)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + (i*2));
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertFalse(l->isPattern());
}

test(isPattern_Line_Broken)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i == 2 || i == 3 || i == 4 || i == 5)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 1);
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertFalse(l->isPattern());
}

#endif;