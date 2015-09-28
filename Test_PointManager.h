#pragma once

#if BUILD_TYPE == FOR_TEST

#include "PointManager.h"

test(PointManager_Setup)
{
	PointManager _pointManager;
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	assertEqual(iter.getNode()->getValue().getState(), HEAD);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter++;
		assertEqual(iter.getNode()->getValue().getState(), NULLPOINT);
	}
	iter++;
	assertEqual(iter.getNode()->getValue().getState(), TAIL);
}

test(PointManager_Setup_Points)
{
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		assertEqual(iter.getNode()->getValue().getAngle(), i);
		assertEqual(iter.getNode()->getValue().getState(), DATA);
		iter++;
	}
	assertEqual(iter.getNode()->getValue().getState(), TAIL);
}

test(PointManager_Get_startPoint)
{
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	assertEqual(_pointManager.getStartPoint()->getAngle(), 0);
}

test(PointManager_Get_endPoint)
{
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	assertEqual(_pointManager.getEndPoint()->getAngle(), L_POINTS_IN_PATTERN - 1);
}

test(PointManager_Adding_Points)
{
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN * 2; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	iter++;
	for (int i = L_POINTS_IN_PATTERN; i < L_POINTS_IN_PATTERN * 2; i++)
	{
		assertEqual(iter.getNode()->getValue().getAngle(), i);
		iter++;
	}
}

test(PointManager_isPattern_StraightLine)
{
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter.getNode()->getValue().setXY(i, i);
		iter++;
	}
	assertTrue(_pointManager.isPattern());
}

test(PointManager_isPattern_MinorDeviation)
{
	//a line that has slight noise
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
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
	assertTrue(_pointManager.isPattern());
}

test(PointManager_isPattern_HeavyDeviation)
{
	//a line that has alot of noise
	//probably not a line
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + 4);
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertFalse(_pointManager.isPattern());
}

test(PointManager_isPattern_SlightCurve)
{
	//minor curvature to line
	//should be a line still
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + i / 5);
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertTrue(_pointManager.isPattern());
}

test(PointManager_isPattern_HeavyCurve)
{
	//heavy curvature to line
	//should not be a line pattern
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		if (i % 2 == 0)
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10 + (i * 2));
			iter++;
		}
		else
		{
			iter.getNode()->getValue().setXY(((i + 1) * 30), 10);
			iter++;
		}
	}
	assertFalse(_pointManager.isPattern());
}

test(PointManager_isPattern_LineBroken)
{
	//broken line - noise in background
	PointManager _pointManager;
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_pointManager.addPoint(i, i);
	}
	DoublyLinkedNodeIterator<Point> iter(*_pointManager.getPointList());
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
	assertFalse(_pointManager.isPattern());
}

#endif