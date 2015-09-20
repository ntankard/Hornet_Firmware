#pragma once

#include "LidarNavigation.h"
#include "math.h"


LidarNavigation::LidarNavigation(HornetManager *theHornetManager, Error *theError)
{
	_e = theError;
	_hornetManager = theHornetManager;
}

LidarNavigation::LidarNavigation()
{
	Point* headPoint = new Point(HEAD);
	head = new PointNode(*headPoint);
	Point* tailPoint = new Point(TAIL);
	PointNode* tail = new PointNode(*tailPoint);
	head->insertAfter(*tail);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		Point* point = new Point(NULLPOINT);
		PointNode* node = new PointNode(*point);
		head->insertAfter(*node);
	}
}

void LidarNavigation::setupPoints(float angle, float distance)
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter = iter.last();
	iter--;
	if ((*iter).getState() == DATA)
	{
		_setup = true;
		newLidarPoint(angle, distance); //call here so we don't lose a point
	}
	else
	{
		iter = iter.first();
		for (iter; (*iter).getState() != NULLPOINT; iter++)
		{
			//goes to the next NULLPOINT
		}
		(*iter).setPoint(angle, distance, DATA);
	}
}

void LidarNavigation::processLidarData(float angle, float distance)
{
	if (!_setup) 
	{
		setupPoints(angle, distance);
	}
	else
	{
		newLidarPoint(angle, distance);
		if (isPattern())
		{
			createPattern();
		}
	}	
}

void LidarNavigation::newLidarPoint(float angle, float distance)
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	PointNode* node = iter.getNode();
	iter.getNode()->dropNode();
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
	iter = iter.last();
	iter--;
	(*iter).setPoint(angle, distance);
}


PointNode* LidarNavigation::getHead()
{
	return head;
}

Pattern* LidarNavigation::getPattern()
{
	return pattern;
}

bool LidarNavigation::isPattern()
{
	//if all your points drawn into lines have an average angle offset less than or equal to
	//the L_LINE_TO_LINE_OFFSET then you can return true otherwise return false
	float angleOfBestFit = 0;
	float angles[L_POINTS_IN_PATTERN - 1];
	float x1;
	float x2;
	float y1;
	float y2;
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	for (int i = 0; i < L_POINTS_IN_PATTERN - 1; i++)
	{
		x1 = iter.getNode()->getValue().getX();
		y1 = iter.getNode()->getValue().getY();
		iter++;
		x2 = iter.getNode()->getValue().getX();
		y2 = iter.getNode()->getValue().getY();
		angles[i] = atan((y2 - y1) / (x2 - x1)) * 180 / PI;
	}
	angleOfBestFit = angles[0];
	for (int i = 1; i < L_POINTS_IN_PATTERN - 1; i++)
	{
		if ((abs(angles[i]) - abs(angleOfBestFit)) < L_LINE_TO_LINE_OFFSET)
		{
			angleOfBestFit = angleOfBestFit * (i-1) + angles[i];
			angleOfBestFit = angleOfBestFit / i;
		}	
		else
		{
			return false;
		}
	}
	return true;
}


bool LidarNavigation::isFeature(Pattern* startPattern, Pattern* endPattern)
{
	if (abs(startPattern->getEndCoordX() - endPattern->getStartCoordX()) <= L_PATTERN_RANGE_IN_FEATURE)
	{
		if (abs(startPattern->getEndCoordY() - endPattern->getStartCoordY()) <= L_PATTERN_RANGE_IN_FEATURE)
		{
			if (abs(startPattern->getAngle() - endPattern->getAngle()) < 90 + L_FEATURE_CORNER_ANGLE_TOLERANCE && abs(startPattern->getAngle() - endPattern->getAngle()) > 90 - L_FEATURE_CORNER_ANGLE_TOLERANCE)
			{
				return true;
			}
		}
	}
	return false;
}

bool LidarNavigation::isAnchor()
{
	//if you have have a recurring feature over..
	L_FEATURE_RECURRENCE_IN_ANCHOR;
	return true;
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

void LidarNavigation::createPattern() 
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	Point* start_point = &iter.getNode()->getValue();
	iter = iter.last();
	iter--;
	Point* end_point = &iter.getNode()->getValue();
	pattern = new Pattern(start_point, end_point);
	start_point = NULL;
	end_point = NULL;
}



/*void LidarNavigation::newLidarPoint(float angle, float distance)
{
	// add point to a node at the end of the linked nodes
	Point* point = new Point(angle, distance);
	PointNode* node = new PointNode(*point);
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
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

LidarNavigation::LidarNavigation()
{
Point* headPoint = new Point(2000, 10000);
head = new PointNode(*headPoint);
Point* tailPoint = new Point(10000, 2000);
PointNode* tail = new PointNode(*tailPoint);
head->insertAfter(*tail);
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
}*/