#pragma once 

#include "PatternManager.h"

PatternManager::PatternManager()
{
	_startPattern = new Pattern(NOT_SET);
	_endPattern = new Pattern(NOT_SET);
	_setup = false;
}

void PatternManager::addPattern(Point* startPoint, Point* endPoint)
{
	if (!_setup)
	{
		setupPattern(startPoint, endPoint);
	}
	else
	{
		Pattern* temp = _startPattern;
		_startPattern = _endPattern;
		_endPattern = temp;
		_endPattern->setPattern(startPoint, endPoint);
	}
}

void PatternManager::setupPattern(Point* startPoint, Point* endPoint)
{
	if (_startPattern->getState() == NOT_SET)
	{
		_startPattern->setPattern(startPoint, endPoint);
		_startPattern->setState(SET);
	} 
	else if (_endPattern->getState() == NOT_SET)
	{
		_endPattern->setPattern(startPoint, endPoint);
		_endPattern->setState(SET);
		_setup = true;
	}	
}

bool PatternManager::isSetup()
{
	return _setup;
}