#pragma once

#if BUILD_TYPE == FOR_TEST

#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"
#include <iostream>
using namespace std;

test(DoublyLinkedNodeIterator_Setup)
{
	typedef DoublyLinkedNode<Point>::Node PointNode;

	Point p1 = Point(1, 100);
	Point p2 = Point(1, 100);
	Point p3 = Point(1, 100);
	Point p4 = Point(1, 100);
	Point p5 = Point(1, 100);
	Point p6 = Point(1, 100);


	PointNode n1(p1);
	PointNode n2(p2);
	PointNode n3(p3);
	PointNode n4(p4);
	PointNode n5(p5);
	PointNode n6(p6);

	DoublyLinkedNodeIterator<Point> iter(n1);

	iter--;


	cout << "Forward iteration I:" << endl;
	for (iter++; iter != iter.rightEnd(); iter++)
	{
		cout << *iter << endl;
	}
	


	cout << "Backward iteration I:" << endl;
	for (iter--; iter != iter.leftEnd(); iter--)
	{
		cout << *iter << endl;
	}


	cout << "Forward iteration II:" << endl;
	for (iter = iter.first(); iter != iter.rightEnd(); ++iter)
	{
		cout << *iter << endl;
	}


	cout << "Backward iteration II:" << endl;
	for (iter = iter.last(); iter != iter.leftEnd(); --iter)
	{
		cout << *iter << endl;
	}
}
#endif