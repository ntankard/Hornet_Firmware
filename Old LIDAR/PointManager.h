#pragma once

#include "CONFIG.h"
 #include "Point.h"
#include "DoublyLinkedNodeIterator.h"
#include "CircularBuffer.h"
/*
class PointManager
{
public:
	void addPoint(float angle, float distance);
private:
	CircularBuffer<Point, L_POINTS_IN_PATTERN> _ponts;
};
*/

typedef DoublyLinkedNode<Point>::Node PointNode;

class PointManager
{
public:
	PointManager();
	void addPoint(float angle, float distance);
	void setupPoint(float angle, float distance);
	bool isPattern();
	Point* getStartPoint();
	Point* getEndPoint();
	PointNode* getPointList();
private:
	bool _setup;
	PointNode* _pointList;
	Point _points[L_POINTS_IN_PATTERN + 2];
	PointNode _nodes[L_POINTS_IN_PATTERN + 2];
};
