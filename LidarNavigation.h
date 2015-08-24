#pragma once

#include "HornetManager.h"
#include "Error.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"

typedef DoublyLinkedNode<Point>::Node PointNode;

class LidarNavigation
{
public:
	LidarNavigation(HornetManager *theHornetManager, Error *theError);

	LidarNavigation();//used for testing

	void newLidarPoint(float angle, float distance);

	void EOSweep(float pitch, float roll, float yaw);

	PointNode* getHead();

	void removePoint(); //removes a point from the start of the linkednodes, ONLY gets called when list is full

	int getSize(); //gets the size of the doublylinkednodes *excludes head and tail

private:

	HornetManager *_hornetManager;
	Error *_e;
	PointNode* head;
};


