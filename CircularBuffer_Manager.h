#pragma once
#include "Error.h"

/**
 * \class	CircularBuffer_Manager
 *
 * \brief	Manages the indexing of a circular buffer
 * 			
 *			This object is used to manage a circular buffer were the buffer itself needs to be stored externaly
 *
 * \author	Nicholas
 * \date	1/08/2015
 *
 * \tparam	Size	Size of the buffer
 */
template<int Size>
class CircularBuffer_Manager
{
public:

	/**
	 * \fn	CircularBuffer_Manager::CircularBuffer_Manager()
	 *
	 * \brief	Default constructor.
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 */
	CircularBuffer_Manager(Error *e)
	{
		_e = e;
		_start = 0;
		_end = 0;
	}

	/**
	 * \fn	bool CircularBuffer_Manager::isEmpty()
	 *
	 * \brief	Query if this object is empty.
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \return	true if empty, false if not.
	 */
	bool isEmpty()
	{
		return _start == _end;
	}

	/**
	 * \fn	bool CircularBuffer_Manager::isFull()
	 *
	 * \brief	Query if this object is full.
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \return	true if full, false if not.
	 */
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

	/**
	 * \fn	int CircularBuffer_Manager::add(Error *e)
	 *
	 * \brief	Adds a object to the buffer
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \throw	E_ILLEGAL_ACCESS	If full
	 *
	 * \return	The index to add the object
	 */
	int add()
	{
		if (isFull())
		{
			_e->add(E_ILLEGAL_ACCESS, "Attempting to add to a full buffer");
			return -1;
		}

		int toRemove = _start;

		_start++;
		if (_start >= Size)
		{
			_start = 0;
		}

		return toRemove;
	}

	/**
	 * \fn	int CircularBuffer_Manager::remove(Error *e)
	 *
	 * \brief	Removes an object from the buffer
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \throw	E_ILLEGAL_ACCESS	If full
	 *
	 * \return	The index of the object to remove
	 */
	int remove()
	{
		if (isEmpty())
		{
			_e->add(E_ILLEGAL_ACCESS, "Attempting to remove from an empty buffer");
			return -1;
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

	/** \brief	The index to add to. */
	int _start;

	/** \brief	The index to remove from. */
	int _end;

	/** \brief	The systems error object */
	Error *_e;
};

