#pragma once
#include "Error.h"

/**
 * \class	CircularBuffer_Manager
 *
 * \brief	Manages the indexing of a circular buffer
 * 			
 *			This object is used to manage a circular buffer where the buffer itself needs to be stored externally
 *
 * \tparam	Size	Size of the buffer
 */
template<int Size>
class CircularBuffer_Manager
{
public:

	/**
	 * \brief	Default constructor
	 *
	 * \param	e	The shared error object
	 */
	CircularBuffer_Manager(volatile Error *e)
	{
		_e = e;
		_start = 0;
		_end = 0;
		_size = 0;
	}

	/**
	* \brief	Default constructor
	*/
	CircularBuffer_Manager()
	{
		_e = NULL;
		_start = 0;
		_end = 0;
	}

	/**
	* \brief	Sets the shared error object (this lets a default contructor exist)
	*
	* \param	e	The shared error object
	*/
	void setError(volatile Error *e)
	{
		_e = e;
	}

	/**
	 * \fn	bool CircularBuffer_Manager::isEmpty()
	 *
	 * \brief	Query if this object is empty
	 *
	 * \return	true if empty, false if not
	 */
	bool isEmpty()
	{
		if (_size == 0)
		{
			return true;
		}
		return false;
	}

	/**
	 * \fn	bool CircularBuffer_Manager::isFull()
	 *
	 * \brief	Query if this object is full
	 *
	 * \return	true if full, false if not
	 */
	bool isFull()
	{
		if (_size == Size)
		{
			return true;
		}
		return false;
	}

	/**
	* \brief	The number of objects in the buffer
	*
	* \return	The Size
	*/
	int size()
	{
		return _size;
	}

	/**
	 * \fn	int CircularBuffer_Manager::add(Error *e)
	 *
	 * \brief	Adds a object to the buffer
	 *
	 * \throw	E_ILLEGAL_ACCESS	If full
	 *
	 * \return	The index to add the object
	 */
	int add()
	{
		if (isFull())
		{
			if (_e != NULL){
				_e->add(E_BUFFER_OVERFLOW, __LINE__);
			}
			return 0;
		}

		_size++;

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
	 * \throw	E_ILLEGAL_ACCESS	If full
	 *
	 * \return	The index of the object to remove
	 */
	int remove()
	{
		if (isEmpty())
		{
			if (_e != NULL){
				_e->add(E_BUFFER_OVERFLOW, __LINE__);
			}
			return 0;
		}

		_size--;

		int toRemove = _end;

		_end++;
		if (_end >= Size)
		{
			_end = 0;
		}

		return toRemove;
	}


private:

	/** \brief	The index to add to */
	int _start;

	/** \brief	The index to remove from */
	int _end;

	/** \brief	The system's error object */
	volatile Error *_e;

	/** \brief	The number of objects in the buffer */
	int _size;
};

