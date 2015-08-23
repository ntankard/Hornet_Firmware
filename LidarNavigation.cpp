#pragma once

#include "LidarNavigation.h"


LidarNavigation::LidarNavigation(HornetManager *theHornetManager, Error *theError)
{
	_e = theError;
	_hornetManager = theHornetManager;

}

LidarNavigation::LidarNavigation() {}

DoublyLinkedNodeIterator<Point*> LidarNavigation::getIter()
{
	return *iter;
}

void LidarNavigation::newLidarPoint(float angle, float distance)
{
	// add point to a node at the end of the linked nodes
	Point* point = new Point(angle, distance);
	PointNode* node = new PointNode(point);
	iter = new DoublyLinkedNodeIterator<Point*>(*node);

}

void LidarNavigation::EOSweep(float pitch, float roll, float yaw)
{
	// compare sweeps, look for ancors
}
