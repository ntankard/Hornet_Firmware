template<class DataType>
class DoublyLinkedNode
{
public:
	typedef DoublyLinkedNode<DataType> Node;

private:
	DataType* fValue;
	Node* fNext;
	Node* fPrevious;

public:
	static Node NIL;

	DoublyLinkedNode() : fValue((DataType*)0),
		fNext(&NIL),
		fPrevious(&NIL)
	{}

	DoublyLinkedNode(DataType& aValue)
	{
		fValue = &aValue;
		fNext = &NIL;
		fPrevious = &NIL;
	}

	void setValue(DataType& aValue)
	{
		fValue = &aValue;
	}

	void insertAfter(Node& aNode)
	{
		aNode.fNext = fNext;
		aNode.fPrevious = this;
		if (fNext != &NIL)
		{
			aNode.fNext = fNext;
			fNext->fPrevious = &aNode;
		}
		fNext = &aNode;
	}

	void insertBefore(Node& aNode)
	{
		
		aNode.fNext =  this;
		if (fPrevious != &NIL)
		{
			aNode.fPrevious = fPrevious;
			fPrevious->fNext = &aNode;
		}
		fPrevious =  &aNode;
	}

	//CANNOT DROP FIRST AND LAST NODES THAT ARE LINKED TO START AND FINISH
	void dropNode()
	{
		if (fPrevious != &NIL)
		{
			fPrevious->fNext = fNext;
		}

		if (fNext != &NIL)
		{
			fNext->fPrevious = fPrevious;
		}
	}

	DataType& getValue() const
	{
		return *fValue;
	}

	Node& getNext() const
	{
		return *fNext;
	}
	Node& getPrevious() const
	{
		return *fPrevious;
	}
};

template<class DataType>

DoublyLinkedNode<DataType> DoublyLinkedNode<DataType>::NIL;