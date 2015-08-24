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

void LidarNavigation::processLidarData(float angle, float distance)
{
	if (getSize() >= L_POINTS_IN_PATTERN)
	{
		removePoint();
	}
	newLidarPoint(angle, distance);

	if (getSize() == 10) //you have enough to start looks for patterns/features/anchors
	{
		if (isPattern())
		{
			//copy DoublyLinkedNodes and assign type as Pattern
		}
		if (isFeature())
		{

		}
		if (isAnchor())
		{

		}
	}
}

bool LidarNavigation::isPattern()
{
	//if all your points drawn into lines have an average angle offset less than or equal to
	//the L_LINE_TO_LINE_OFFSET then you can return true otherwise return false
}

bool LidarNavigation::isFeature()
{
	//if you have 2 patterns at 90 degree
	L_PATTERNS_IN_CORNER_FEATURE;
	return true;
}

bool LidarNavigation::isAnchor()
{
	//if you have have a recurring feature over..
	L_FEATURE_RECURRENCE_IN_ANCHOR;
	return true;
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

void LidarNavigation::removePoint()
{
	// delete point and node at the start of the linked nodes
	// should check if there is actually data to delete so you don't accidentally
	// delete head and tail, however this function is only called under certain condition
	// therefore another check will be a waste of time
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	const PointNode* node = iter.getNode(); //get a reference to the Node we are deleting
	const Point* point = &(*iter); //get a reference to the Point we are deleting
	iter.getNode()->dropNode();
	delete node;
	delete point;
}

int LidarNavigation::getSize()
{
	int count = 0;
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head); //head
	iter++; //first data member
	DoublyLinkedNodeIterator<Point> iterEnd = DoublyLinkedNodeIterator<Point>(*head);
	iterEnd = iterEnd.last(); //tail
	for (count; iter != iterEnd; count++)
	{
		iter++;
	}
	return count;
}

void LidarNavigation::EOSweep(float pitch, float roll, float yaw)
{
	// compare sweeps, look for ancors
}
