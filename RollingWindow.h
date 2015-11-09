#pragma once

#include "CircularBuffer.h"

/**
* \brief	A Rollwing window buffer
*
* \tparam	T		The type of the object
* \tparam	Size	Size of the Window
*/
template<class T, int Size>
class RollingWindow
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	e	The shared error object
	*/
	RollingWindow(volatile Error *e) :_window(e)
	{
		_e = e;
	}

	/**
	* \brief	Adds a object to the window (or shift the window)
	*
	* \param	toAdd	The object to add
	*/
	T add(T toAdd)
	{
		T toReturn;
		if (_window.isFull())
		{
			// full window
			toReturn = _window.remove();
			_window.add(toAdd);

			return toReturn;
		}
		else
		{
			_window.add(toAdd);
			return toAdd;	
		}
	}

	bool isFull()
	{
		return _window.isFull();
	}

	int getSize()
	{
		_window.size();
	}

private:

	/** \brief	The Window */
	CircularBuffer<T, Size> _window;

	/** \brief	The systems error object */
	volatile Error *_e;
};
