#pragma once

#include "DoublyLinkedNode.h"

template<class DataType>
class DoublyLinkedNodeIterator
{
private:
	enum IteratorState { BEFORE, DATA, AFTER };

	IteratorState fState;

	typedef DoublyLinkedNode<DataType> Node;
	
	Node* fLeftmost;
	Node* fRightmost;
	Node* fCurrent;
public:
	typedef DoublyLinkedNodeIterator<DataType> Iterator;

	DoublyLinkedNodeIterator(Node& aList)
	{
		for (Node* lNode = &aList; lNode != &Node::NIL; lNode = &lNode->getNext())
		{
			fRightmost = lNode;
		}

		for (Node* lNode = &aList; lNode != &Node::NIL; lNode = &lNode->getPrevious())
		{
			fLeftmost = lNode;
		}
		fCurrent = fLeftmost;

		fState = DATA;
	}

	const DataType& operator*() const
	{
		return fCurrent->getValue();
	}
	
	Iterator& operator++()
	{
		if (fState != BEFORE)
		{
			fCurrent = &(fCurrent->getNext());
	
			if((fCurrent == &Node::NIL))
				fState = AFTER;
			else
				fState = DATA;
		}
		else 
		{
			fCurrent = fLeftmost;
			fState = DATA;
		}

		return *this;
	}

	Iterator operator++(int)
	{
		Iterator temp = *this;

		++(*this);

		return temp;
	}

	Iterator& operator--()
	{
		if (fState != AFTER)
		{
			fCurrent = &(fCurrent->getPrevious());

			if (fCurrent == &Node::NIL)
				fState = BEFORE;
			else
				fState = DATA;
		}
		else 
		{
			fCurrent = fRightmost;
			fState = DATA;
		}

		return *this;
	}

	Iterator operator--(int)
	{
		Iterator temp = *this;
		
		--(*this);

		return temp;
	}


	bool operator==(const Iterator& aOtherIter) const
	{
		return fCurrent == aOtherIter.fCurrent
			&& fLeftmost == aOtherIter.fLeftmost
			&& fRightmost == aOtherIter.fRightmost
			&& fState == aOtherIter.fState;
	}

	bool operator!=(const Iterator& aOtherIter) const
	{
		return ! (*this == aOtherIter);
	}
	

	Iterator leftEnd() const
	{
		Iterator lIterator = --(first());
		return lIterator;
	}

	Iterator first() const
	{
		
		Iterator lIterator = Iterator(*fLeftmost);
		lIterator.fCurrent = lIterator.fLeftmost;
		return lIterator;
	}
	
	Iterator last() const
	{
		Iterator lIterator = Iterator(*fRightmost);
		lIterator.fCurrent = lIterator.fRightmost;
		return lIterator;
	}
	
	Iterator rightEnd() const
	{
		Iterator lIterator = ++(last());
		return lIterator;
	}

	Node* getNode()
	{
		return fCurrent;
	}
};