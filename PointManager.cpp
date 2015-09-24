#pragma once 

#include "PointManager.h"

PointManager::PointManager()
{
	_points[0] = Point(HEAD); //headPoint
	_nodes[0].setValue(_points[0]);
	_points[L_POINTS_IN_PATTERN + 1] = Point(TAIL); //tailPoint
	_nodes[L_POINTS_IN_PATTERN + 1].setValue(_points[L_POINTS_IN_PATTERN + 1]);
	_pointList = &_nodes[0];
	_pointList->insertAfter(_nodes[L_POINTS_IN_PATTERN + 1]);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_points[i+1] = Point(NULLPOINT);
		_nodes[i+1].setValue(_points[i+1]);
		_pointList->insertAfter(_nodes[i + 1]);
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

Point* PointManager::getStartPoint()
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*_pointList);
	iter++;
	return &iter.getNode()->getValue();
}

Point* PointManager::getEndPoint()
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*_pointList);
	iter = iter.last();
	iter--;
	return &iter.getNode()->getValue();
}

PointNode* PointManager::getPointList()
{
	return _pointList;
}