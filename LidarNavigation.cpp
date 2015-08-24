#pragma once

#include "LidarNavigation.h"


LidarNavigation::LidarNavigation(HornetManager *theHornetManager, Error *theError)
{
	_e = theError;
	_hornetManager = theHornetManager;
}

LidarNavigation::LidarNavigation() 
{
	Point* headPoint = new Point(2000, 10000);
	head = new PointNode(*headPoint);
	Point* tailPoint = new Point(10000, 2000);
	PointNode* tail = new PointNode(*tailPoint);
	head->insertAfter(*tail);
}

PointNode* LidarNavigation::getHead()
{
	return head;
}


void LidarNavigation::newLidarPoint(float angle, float distance)
{
	// add point to a node at the end of the linked nodes
	Point* point = new Point(angle, distance);
	PointNode* node = new PointNode(*point);
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
}

void LidarNavigation::EOSweep(float pitch, float roll, float yaw)
{
	// compare sweeps, look for ancors
}
