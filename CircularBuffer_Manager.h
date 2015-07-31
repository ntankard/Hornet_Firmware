#pragma once
#include "Arduino.h"

template<int Size>
class CircularBuffer_Manager
{
public:
	CircularBuffer_Manager()
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

	int add()
	{
		if (isFull())
		{
			Serial.print("over flow");
			return -1; //@TODO replace with throw
		}

		int toRemove = _start;

		_start++;
		if (_start >= Size)
		{
			_start = 0;
		}

		return toRemove;
	}


	int remove()
	{
		if (isEmpty())
		{
			Serial.print("under flow");
			return -1;	//@TODO replace with throw
		}

		int toRemove = _end;

		_end++;
		if (_end >= Size)
		{
			_end = 0;
		}

		return toRemove;
	}


private:

	int _start;
	int _end;
};

