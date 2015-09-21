#pragma once 

#include "PointManager.h"

PointManager::PointManager()
{
	Point* headPoint = new Point(HEAD);
	_pointList = new PointNode(*headPoint);
	Point* tailPoint = new Point(TAIL);
	PointNode* tail = new PointNode(*tailPoint);
	_pointList->insertAfter(*tail);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		Point* point = new Point(NULLPOINT);
		PointNode* node = new PointNode(*point);
		_pointList->insertAfter(*node);
	}
	_setup = false;
}

void PointManager::addPoint(float angle, float distance)
{
	if (!_setup)
	{
		setupPoint(angle, distance);
	}
	else
	{
		DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*_pointList);
		iter++;
		PointNode* node = iter.getNode();
		iter.getNode()->dropNode();
		iter = iter.last();
		iter.getNode()->insertBefore(*node);
		iter = iter.last();
		iter--;
		iter.getNode()->getValue().setPoint(angle, distance);
	}
}

void PointManager::setupPoint(float angle, float distance)
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*_pointList);
	iter = iter.first();
	for (iter; iter.getNode()->getValue().getState() != NULLPOINT; iter++)
	{
		//goes to the next NULLPOINT
	}
	iter.getNode()->getValue().setPoint(angle, distance, DATA);
	iter = iter.last();
	iter--;
	if (iter.getNode()->getValue().getState() == DATA)
	{
		_setup = true;
	}
}

bool PointManager::isPattern()
{
	//if all your points drawn into lines have an average angle offset less than or equal to
	//the L_LINE_TO_LINE_OFFSET then you can return true otherwise return false
	if (_setup)
	{
		float angleOfBestFit = 0;
		float angles[L_POINTS_IN_PATTERN - 1];
		float x1;
		float x2;
		float y1;
		float y2;
		DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*_pointList);
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
				angleOfBestFit = angleOfBestFit * (i - 1) + angles[i];
				angleOfBestFit = angleOfBestFit / i;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

PointNode* PointManager::getPointList()
{
	return _pointList;
}