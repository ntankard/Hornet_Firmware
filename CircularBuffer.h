#pragma once

template<class T,int Size>
class CircularBuffer
{
public:
	CircularBuffer()
	{
		_start = 0;
		_end = 0;
	}

	bool isEmpty()
	{
		return _start == _end;
	}


	bool isFull()
	{
		if (_end == 0 && (_start - 1) == Size)
		{
			return true;
		}

		if (_start == (_end - 1))
		{
			return true;
		}

		return false;
	}

	void add(T toAdd)
	{
		if (isFull())
		{
			return; //@TODO replace with throw
		}

		_bufferr[_start];

		_start++;
		if (_start == Size)
		{
			_start = 0;
		}
	}


	T remove()
	{
		T removed;
		if (isEmpty())
		{
			return removed;	//@TODO replace with throw
		}

		removed = _bufferr[_end];

		_end++;
		if (_end == Size)
		{
			_end = 0;
		}

		return removed;
	}


private:

	int _start;
	int _end;

	T _bufferr[Size];
};

