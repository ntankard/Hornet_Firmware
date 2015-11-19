#pragma once

#include "MessageBuffer.h"
#include "Point.h"
#include "Error.h"
#include "AnchorDetector.h"

/**
* \class	AnchorManager
*
* \brief	Mange the lifecyle of anchors (in progress)
*/
class AnchorManager
{
public:
	AnchorManager(volatile Error* e);
	volatile MessageBuffer_Passer* getNextRegister();
	void newPoint(Point p);

private:

	volatile MessageBuffer_Passer* _anchors[4];

	volatile MessageBuffer<MB_ANCHOR_1, 2> _anchor_1;
	volatile MessageBuffer<MB_ANCHOR_2, 2> _anchor_2;
	volatile MessageBuffer<MB_ANCHOR_3, 2> _anchor_3;
	volatile MessageBuffer<MB_ANCHOR_4, 2> _anchor_4;
	int _registerAccsessed;

	AnchorDetector _anchorDetector;
};

