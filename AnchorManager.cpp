#include "AnchorManager.h"


AnchorManager::AnchorManager(volatile Error* e) :_anchorDetector(e)
{
	_anchors[0] = &_anchor_1;
	_anchors[1] = &_anchor_2;
	_anchors[2] = &_anchor_3;
	_anchors[3] = &_anchor_4;

	_registerAccsessed = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* AnchorManager::getNextRegister()
{
	volatile MessageBuffer_Passer* toReturn = _anchors[_registerAccsessed];

	_registerAccsessed++;
	if (_registerAccsessed >= 4)
	{
		_registerAccsessed = 0;
	}

	return toReturn;
}

//-----------------------------------------------------------------------------------------------------------------------------

void AnchorManager::newPoint(Point p)
{
	if (_anchorDetector.newPoint(p))
	{
		Anchor a = _anchorDetector.getLast();
		Point p = a.getAnchorPoint();

		_anchor_1.getData()[0] = a.getStart().getStart().getAngle() * 90;
		_anchor_1.getData()[1] = a.getStart().getStart().getDistance();

		_anchor_2.getData()[0] = a.getStart().getEnd().getAngle() * 90;
		_anchor_2.getData()[1] = a.getStart().getEnd().getDistance();

		_anchor_3.getData()[0] = a.getEnd().getStart().getAngle() * 90;
		_anchor_3.getData()[1] = a.getEnd().getStart().getDistance();

		_anchor_4.getData()[0] = a.getEnd().getEnd().getAngle() * 90;
		_anchor_4.getData()[1] = a.getEnd().getEnd().getDistance();
	}
}
