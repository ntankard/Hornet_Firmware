#pragma once

#include "HornetManager.h"
#include "Error.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"

class LidarNavigation
{
public:
	LidarNavigation(HornetManager *theHornetManager, Error *theError);

	LidarNavigation();//used for testing

	void newLidarPoint(float angle, float distance);

	void EOSweep(float pitch, float roll, float yaw);

	DoublyLinkedNodeIterator<Point*> getIter();

private:

	HornetManager *_hornetManager;
	Error *_e;

	typedef DoublyLinkedNode<Point*>::Node PointNode;
	DoublyLinkedNodeIterator<Point*> *iter = NULL;

};


