#pragma once

#include "CONFIG.h"

template<int SIZE>
class PriorityManager 
{
public:

	PriorityManager()
	{
		_currentIndex = SIZE;
		for (int i = 0; i < SIZE; i++)
		{
			_runCount[i] = 0;
			_priority[i] = 1;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int setPriority(int i, int pri)
	{
		if (i < SIZE && i >= 0)
		{
			_priority[i] = pri;
		}
		else
		{
			TP("ERROR");
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getNextIndex()
	{
		// keep looping until a thread runs (this will lock if all thread are 0)
		while(true){

			_currentIndex++;
			if (_currentIndex >= SIZE)
			{
				_currentIndex = 0;
			}

			if (_priority[_currentIndex] != 0)
			{
				_runCount[_currentIndex]++;
				if (_runCount[_currentIndex] >= _priority[_currentIndex])
				{
					_runCount[_currentIndex] = 0;
					return _currentIndex;
				}
			}
			else
			{
				_runCount[_currentIndex] = 0;
			}
		}
		return 0;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

private:
	int _runCount[SIZE];
	int _priority[SIZE];
	int _currentIndex;
};