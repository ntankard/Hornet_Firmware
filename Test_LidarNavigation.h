#pragma once

#include "LidarNavigation.h"

#if BUILD_TYPE == FOR_TEST

test(LidarNavigation_newLidarPoint)
{
	LidarNavigation* l = new LidarNavigation();
	l->newLidarPoint(1, 100);
	DoublyLinkedNodeIterator<Point*> iter = l->getIter();
	assertEqual((*iter)->getAngle(), 1);
}

#endif;
