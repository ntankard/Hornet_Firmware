#pragma once

#if BUILD_TYPE == FOR_TEST

#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"

test(DoublyLinkedNodeIterator_Setup)
{
	//test with ints
	typedef DoublyLinkedNode<int>::Node IntNode;

	int p1 = 1;
	int p2 = 2;
	int p3 = 3;
	int p4 = 4;
	int p5 = 5;
	int p6 = 6;


	IntNode n1(p1);
	IntNode n2(p2);
	IntNode n3(p3);
	IntNode n4(p4);
	IntNode n5(p5);
	IntNode n6(p6);

	DoublyLinkedNodeIterator<int> iter(n1);

	iter--;
	/**
	typedef DoublyLinkedNode<Point>::Node PointNode;

	Point p1 = Point(1, 100);
	Point p2 = Point(2, 200);
	Point p3 = Point(3, 300);
	Point p4 = Point(4, 400);
	Point p5 = Point(5, 500);
	Point p6 = Point(6, 600);


	PointNode n1(p1);
	PointNode n2(p2);
	PointNode n3(p3);
	PointNode n4(p4);
	PointNode n5(p5);
	PointNode n6(p6);

	DoublyLinkedNodeIterator<Point> iter(n1);

	iter--;
	
	//Forward Iteration
	for (iter++; iter != iter.rightEnd(); iter++)
	{

	}
	//assert that it's at right end
	assertEqual(*iter.getAngle(), 6);
	assertEqual(*iter.getDistance(), 600);


	//Backward Iteration
	for (iter--; iter != iter.leftEnd(); iter--)
	{

	}
	//assert that it's at left end
	assertEqual(*iter.getAngle(), 1);
	assertEqual(*iter.getDistance(), 100);


	//Second Node
	if (iter != iter.rightEnd())
	{
		iter++;
	}
	//assert that it's at second node
	assertEqual(*iter.getAngle(), 2);
	assertEqual(*iter.getDistance(), 200);
	*/
}
#endif