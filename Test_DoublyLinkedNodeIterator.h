#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Point.h"
#include "DoublyLinkedNodeIterator.h"

test(DoublyLinkedNodeIterator_Ints)
{
	//-----------------------------------------------------------------------------------------------------------------------------
	// ----------------------------------------------------- TEST INTS ------------------------------------------------------------
	// ----------------------------------------------------------------------------------------------------------------------------
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

	n1.insertAfter(n6);
	n1.insertAfter(n5);
	n1.insertAfter(n4);
	n1.insertAfter(n3);
	n1.insertAfter(n2);

	DoublyLinkedNodeIterator<int> iter(n1);

	iter--;

	for (iter++; iter != iter.rightEnd(); iter++)
	{

	}

	//Are you at the right side?
	iter--; //we minus one to get on the value because we were on END NODE
	assertEqual(*iter, 6);

	for (iter--; iter != iter.leftEnd(); iter--)
	{

	}

	//Are you at the left side?
	iter++; //we add one to get on the value because we were on START NODE
	assertEqual(*iter, 1);

	if (iter != iter.rightEnd())
	{
		iter++; //go to the second node
	}

	//Are you at the second node?
	assertEqual(*iter, 2);
}

test(DoublyLinkedNodeIterator_Points)
{

	//-----------------------------------------------------------------------------------------------------------------------------
	// ----------------------------------------------------- TEST POINTS ----------------------------------------------------------
	// ----------------------------------------------------------------------------------------------------------------------------

	typedef DoublyLinkedNode<Point>::Node PointNode;

	//Point(angle, distance)
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

	n1.insertAfter(n6);
	n1.insertAfter(n5);
	n1.insertAfter(n4);
	n1.insertAfter(n3);
	n1.insertAfter(n2);

	DoublyLinkedNodeIterator<Point> iter(n1);

	iter--;

	for (iter++; iter != iter.rightEnd(); iter++) //go to the right side
	{

	}

	//Are you at the right side?
	iter--; //we minus one to get on the value because we were on END NODE
	assertEqual((*iter).getAngle(), 6);
	assertEqual((*iter).getDistance(), 600);

	for (iter--; iter != iter.leftEnd(); iter--)
	{

	}

	//Are you at the left side?
	iter++; //we add one to get on the value because we were on START NODE
	assertEqual((*iter).getAngle(), 1);
	assertEqual((*iter).getDistance(), 100);

	if (iter != iter.rightEnd())
	{
		iter++; //go to the second node
	}

	//Are you at the second node?
	assertEqual((*iter).getAngle(), 2);
	assertEqual((*iter).getDistance(), 200);
}

test(DoublyLinkedNodeIterator_DroppingNodes)
{

	//-----------------------------------------------------------------------------------------------------------------------------
	// ----------------------------------------------------- TEST DROP NODES ------------------------------------------------------
	// ----------------------------------------------------------------------------------------------------------------------------

	typedef DoublyLinkedNode<Point>::Node PointNode;

	//Point(angle, distance)
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

	n1.insertAfter(n6);
	n1.insertAfter(n5);
	n1.insertAfter(n4);
	n1.insertAfter(n3);
	n1.insertAfter(n2);

	DoublyLinkedNodeIterator<Point> iter(n1);

	//lets delete node 5 and go to the end then go back twice which should place us on node 5 (which has been removed)
	iter--;
	n5.dropNode();
	for (iter++; iter != iter.rightEnd(); iter++) //go to the right side
	{

	}
	iter--;
	iter--;
	assertEqual((*iter).getAngle(), 4);

}

test(DoublyLinkedNodeIterator_DroppingNodesIterator)
{

	//-----------------------------------------------------------------------------------------------------------------------------
	// ----------------------------------------------------- TEST DROP NODES FROM ITERATOR ----------------------------------------
	// ----------------------------------------------------------------------------------------------------------------------------

	typedef DoublyLinkedNode<Point>::Node PointNode;

	//Point(angle, distance)
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

	n1.insertAfter(n6);
	n1.insertAfter(n5);
	n1.insertAfter(n4);
	n1.insertAfter(n3);
	n1.insertAfter(n2);

	DoublyLinkedNodeIterator<Point> iter(n1);

	iter++;
	iter++;
	iter.getNode()->dropNode(); //delete n3
	for (iter--; iter != iter.leftEnd(); iter--)
	{

	}
	iter++;
	iter++;
	iter++; //go to where node 3 WAS.. should now be node 4 though
	assertEqual((*iter).getAngle(), 4);
}


test(DoublyLinkedNodeIterator_PointsPointer)
{

	//-----------------------------------------------------------------------------------------------------------------------------
	// ----------------------------------------------------- TEST POINTER TO POINTS -----------------------------------------------
	// ----------------------------------------------------------------------------------------------------------------------------

	typedef DoublyLinkedNode<Point*>::Node PointNode;

	//Point(angle, distance)
	Point* p1 = new Point(1, 100);
	Point* p2 = new Point(2, 200);
	Point* p3 = new Point(3, 300);
	Point* p4 = new Point(4, 400);
	Point* p5 = new Point(5, 500);
	Point* p6 = new Point(6, 600);

	PointNode n1(p1);
	PointNode n2(p2);
	PointNode n3(p3);
	PointNode n4(p4);
	PointNode n5(p5);
	PointNode n6(p6);

	n1.insertAfter(n6);
	n1.insertAfter(n5);
	n1.insertAfter(n4);
	n1.insertAfter(n3);
	n1.insertAfter(n2);

	DoublyLinkedNodeIterator<Point*> iter(n1);

	iter--;

	for (iter++; iter != iter.rightEnd(); iter++) //go to the right side
	{

	}

	//Are you at the right side?
	iter--; //we minus one to get on the value because we were on END NODE
	assertEqual((*iter)->getAngle(), 6);
	assertEqual((*iter)->getDistance(), 600);

	for (iter--; iter != iter.leftEnd(); iter--) //go to the left side
	{

	}

	//Are you at the left side?
	iter++; //we add one to get on the value because we were on START NODE
	assertEqual((*iter)->getAngle(), 1);
	assertEqual((*iter)->getDistance(), 100);


	//lets delete point objects and remove nodes for 2,3,4,5

	iter++; //go to second node
	//lets keep a reference to the object so we can check if it's been deleted
	delete *iter;
	iter.getNode()->dropNode();
	iter++; //go to third node
	delete *iter;
	iter.getNode()->dropNode();
	iter++; //go to fourth node
	delete *iter;
	iter.getNode()->dropNode();
	iter++; //go to fifth node
	delete *iter;
	iter.getNode()->dropNode();

	for (iter++; iter != iter.rightEnd(); iter++) //go to the right side
	{

	}
	iter--;
	assertEqual((*iter)->getAngle(), 6);
	iter--;
	assertEqual((*iter)->getAngle(), 1);
}

#endif