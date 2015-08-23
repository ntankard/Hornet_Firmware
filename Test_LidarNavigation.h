#pragma once

#include "LidarNavigation.h"

#if BUILD_TYPE == FOR_TEST

test(LidarNavigation_newLidarPoint)
{
	LidarNavigation* l = new LidarNavigation();
	l->newLidarPoint(6, 600);
	DoublyLinkedNodeIterator<Point*> iter = l->getIter();
	assertEqual((*iter)->getAngle(), 6);
}

test(LidarNavigation_MultipleNewLidarPoint)
{

}

#endif;
