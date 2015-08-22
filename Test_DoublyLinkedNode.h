#pragma once

#if BUILD_TYPE == FOR_TEST

#include "DoublyLinkedNode.h"
#include "Point.h"

test(DoublyLinkedNode_Setup)
{
	typedef DoublyLinkedNode<int>::Node IntNode;

	int p1 = 1;

	IntNode n1(p1);

	assertEqual(n1.getValue, 1);
}

#endif