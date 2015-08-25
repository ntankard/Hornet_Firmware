#pragma once

#include "LidarNavigation.h"

#if BUILD_TYPE == FOR_TEST

test(LidarNavigation_newLidarNavigation)
{
	LidarNavigation* l = new LidarNavigation();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	assertEqual((*iter).getAngle(), 2000);
	iter = iter.last();
	assertEqual((*iter).getAngle(), 10000);
}

test(LidarNavigation_newLidarPoint)
{
	LidarNavigation* l = new LidarNavigation();
	l->newLidarPoint(6, 600);
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	assertEqual((*iter).getAngle(), 6);
}

test(LidarNavigation_MultipleNewLidarPoint)
{
	LidarNavigation* l = new LidarNavigation();
	for (int i = 1; i < 7; i++)
	{
		l->newLidarPoint(i, i*100);
	}
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	for (int i = 1; i < 7; i++)
	{
		assertEqual((*iter).getAngle(), i);
		iter++;
	}
}

test(LidarNavigation_Size)
{
	LidarNavigation* l = new LidarNavigation();
	assertEqual(l->getSize(), 0);
	for (int i = 1; i < 7; i++)
	{
		l->newLidarPoint(i, i * 100);
	}
	assertEqual(l->getSize(), 6);
}

test(LidarNavifation_RemovePoint)
{
	LidarNavigation* l = new LidarNavigation();
	assertEqual(l->getSize(), 0);
	for (int i = 1; i < 7; i++)
	{
		l->newLidarPoint(i, i * 100);
	}

	assertEqual(l->getSize(), 6);
	l->removePoint();
	assertEqual(l->getSize(), 5);
	l->removePoint();
	l->removePoint();
	PointNode* node = l->getHead();
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
	iter++;
	assertEqual((*iter).getAngle(), 4); //make sure that it's deleting from the start of the list
	l->removePoint();
	l->removePoint();
	l->removePoint();
	assertEqual(l->getSize(), 0);
}

test(LidarNavifation_ProcessData_LotsofPoints)
{
	LidarNavigation* l = new LidarNavigation();
	for (int i = 1; i < L_POINTS_IN_PATTERN * 2; i++)
	{
		l->processLidarData(10+i, 100);
	}
	assertEqual(l->getSize(), L_POINTS_IN_PATTERN);
}

test(LidarNavifation_ProcessData_CorrectOrder)
{
	//checks if new Points are added to the tail, then removed at the head
	LidarNavigation* l = new LidarNavigation();
	for (int i = 1; i < L_POINTS_IN_PATTERN; i++)
	{
		l->newLidarPoint(i, i * 100);
	}
	PointNode* node = l->getHead();
	for (int i = 1; i < L_POINTS_IN_PATTERN; i++)
	{
		DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*node);
		iter++;
		assertEqual((*iter).getAngle(), i);
		assertEqual((*iter).getDistance(), i*100);
		l->removePoint();
	}
}

#endif

#if BUILD_TYPE == FOR_MEMORY_TEST

test(X_memoryLeak)
{
	LidarNavigation* l = new LidarNavigation();
	while (true)
	{
		l->processLidarData(5, 500);
		Serial.println("running");
	}
}

#endif;
