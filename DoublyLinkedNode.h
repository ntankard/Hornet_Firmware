
template<class DataType>
class DoublyLinkedNode
{
public:
	typedef DoublyLinkedNode<DataType> Node;

private:
	const DataType* fValue;
	Node* fNext;
	Node* fPrevious;

	DoublyLinkedNode(): fValue((const DataType*)0),
						fNext(&NIL),
						fPrevious(&NIL)
	{}

public:
	static Node NIL;

	DoublyLinkedNode(const DataType& aValue)
	{
		fValue = &aValue;
		fNext = &NIL;
		fPrevious = &NIL;
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

	const DataType& getValue() const
	{
		return *fValue;
	}

	const Node& getNext() const
	{
		return *fNext;
	}
	const Node& getPrevious() const
	{
		return *fPrevious;
	}
};

template<class DataType>
DoublyLinkedNode<DataType> DoublyLinkedNode<DataType>::NIL;