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

private:

	HornetManager *_hornetManager;
	Error *_e;
	PointNode* head;
};


