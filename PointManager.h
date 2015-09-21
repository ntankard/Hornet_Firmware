#pragma once

#include "Point.h"

typedef DoublyLinkedNode<Point>::Node PointNode;

class PointManager
{
public:
	PointManager();
	void addPoint(float angle, float distance);
	void setupPoint(float angle, float distance);
	bool isPattern();
	PointNode* gePointList();
private:
	bool _setup;
	PointNode* _pointList;
};