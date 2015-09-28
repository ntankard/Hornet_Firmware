#pragma once 

#include "PointManager.h"

PointManager::PointManager()
{
	_points[0].setState(HEAD); //headPoint
	_nodes[0].setValue(_points[0]);
	_points[L_POINTS_IN_PATTERN + 1].setState(TAIL); //tailPoint
	_nodes[L_POINTS_IN_PATTERN + 1].setValue(_points[L_POINTS_IN_PATTERN + 1]);
	_pointList = &_nodes[0];
	_pointList->insertAfter(_nodes[L_POINTS_IN_PATTERN + 1]);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		_points[i+1].setState(NULLPOINT);
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
		DoublyLinkedNodeIterator<Point> iter(*_pointList);
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
	DoublyLinkedNodeIterator<Point> iter(*_pointList);
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
		#if L_PATTERN_DEFINITION == L_LINE_OF_BEST_FIT
		
		float angleOfBestFit = 0;
		float angles[L_POINTS_IN_PATTERN - 1];
		float x1;
		float x2;
		float y1;
		float y2;
		DoublyLinkedNodeIterator<Point> iter(*_pointList);
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
		#endif

		#if L_PATTERN_DEFINITION == L_POINT_TO_POINT 
		
		float pointToPointAngle = 0;
		float angles[L_POINTS_IN_PATTERN - 1];
		float x1;
		float x2;
		float y1;
		float y2;
		DoublyLinkedNodeIterator<Point> iter(*_pointList);
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
		//Get line from start to end of pattern
		iter = iter.first();
		iter++;
		x1 = iter.getNode()->getValue().getX();
		y1 = iter.getNode()->getValue().getY();
		iter = iter.last();
		iter--;
		x2 = iter.getNode()->getValue().getX();
		y2 = iter.getNode()->getValue().getY();
		pointToPointAngle = atan((y2 - y1) / (x2 - x1)) * 180 / PI;

		for (int i = 0; i < L_POINTS_IN_PATTERN - 1; i++)
		{
			if (!((abs(angles[i]) - abs(pointToPointAngle)) < L_LINE_TO_LINE_OFFSET))
			{
				return false;
			}
			return true;
		}

		#endif

		#if L_PATTERN_DEFINITION == L_END_TO_POINT 
		
		float endToPointAngle = 0;
		float angles[L_POINTS_IN_PATTERN - 1];
		float x1;
		float x2;
		float y1;
		float y2;
		DoublyLinkedNodeIterator<Point> iter(*_pointList);
		//store end point as x2 and y2
		iter = iter.last();
		iter--;
		x2 = iter.getNode()->getValue().getX();
		y2 = iter.getNode()->getValue().getY();
		//reset iter
		iter = iter.first();
		iter++;
		for (int i = 0; i < L_POINTS_IN_PATTERN - 1; i++)
		{
			x1 = iter.getNode()->getValue().getX();
			y1 = iter.getNode()->getValue().getY();
			iter++;
			angles[i] = atan((y2 - y1) / (x2 - x1)) * 180 / PI;
		}
		//store line from end to start
		endToPointAngle = angles[0];
		for (int i = 1; i < L_POINTS_IN_PATTERN - 1; i++)
		{
			if (!((abs(angles[i]) - abs(endToPointAngle)) < L_LINE_TO_LINE_OFFSET))
			{
				return false;
			}
			return true;
		}
		#endif

		#if L_PATTERN_DEFINITION == L_START_TO_POINT 

		float startToPointAngle = 0;
		float angles[L_POINTS_IN_PATTERN - 1];
		float x1;
		float x2;
		float y1;
		float y2;
		DoublyLinkedNodeIterator<Point> iter(*_pointList);
		//store start point as x1 and y1
		iter++;
		x1 = iter.getNode()->getValue().getX();
		y1 = iter.getNode()->getValue().getY();
		
		iter++;

		for (int i = 0; i < L_POINTS_IN_PATTERN - 1; i++)
		{
			x2 = iter.getNode()->getValue().getX();
			y2 = iter.getNode()->getValue().getY();
			iter++;
			angles[i] = atan((y2 - y1) / (x2 - x1)) * 180 / PI;
		}
		//store line from start to end
		startToPointAngle = angles[L_POINTS_IN_PATTERN - 2];

		for (int i = 0; i < L_POINTS_IN_PATTERN - 1; i++)
		{
			if (!((abs(angles[i]) - abs(startToPointAngle)) < L_LINE_TO_LINE_OFFSET))
			{
				return false;
			}
		}
		return true;
		#endif
	}
	return false;
}

Point* PointManager::getStartPoint()
{
	DoublyLinkedNodeIterator<Point> iter(*_pointList);
	iter++;
	return &iter.getNode()->getValue();
}

Point* PointManager::getEndPoint()
{
	DoublyLinkedNodeIterator<Point> iter(*_pointList);
	iter = iter.last();
	iter--;
	return &iter.getNode()->getValue();
}

PointNode* PointManager::getPointList()
{
	return _pointList;
}