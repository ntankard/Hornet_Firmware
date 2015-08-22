#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Point.h"
#include "DoublyLinkedNodeIterator.h"

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
#endif