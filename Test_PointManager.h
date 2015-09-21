#pragma once

#if BUILD_TYPE == FOR_TEST

#include "PointManager.h"

test(PointManager_Setup)
{
	PointManager* _pointManager = new PointManager();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*_pointManager->gePointList());
	assertEqual(iter.getNode()->getValue().getState(), HEAD);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		iter++;
		assertEqual(iter.getNode()->getValue().getState(), NULLPOINT);
	}
	iter++;
	assertEqual(iter.getNode()->getValue().getState(), TAIL);
}

#endif