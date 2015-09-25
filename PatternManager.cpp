#pragma once 

#include "PatternManager.h"

PatternManager::PatternManager()
{
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
		Pattern temp = _enterPattern;
		_enterPattern = _exitPattern;
		_exitPattern = temp;
		_exitPattern.setPattern(startPoint, endPoint);
	}
}

void PatternManager::setupPattern(Point* startPoint, Point* endPoint)
{
	if (_enterPattern.getState() == NOT_SET)
	{
		_enterPattern.setPattern(startPoint, endPoint);
	} 
	else if (_exitPattern.getState() == NOT_SET)
	{
		_exitPattern.setPattern(startPoint, endPoint);
		_setup = true;
	}	
}

bool PatternManager::isFeature()
{
	if (_setup)
	{
		if (abs(_enterPattern.getEndCoordX() - _exitPattern.getStartCoordX()) <= L_PATTERN_RANGE_IN_FEATURE)
		{
			if (abs(_enterPattern.getEndCoordY() - _exitPattern.getStartCoordY()) <= L_PATTERN_RANGE_IN_FEATURE)
			{
				if (abs(_enterPattern.getAngle() - _exitPattern.getAngle()) < 90 + L_FEATURE_CORNER_ANGLE_TOLERANCE && abs(_enterPattern.getAngle() - _exitPattern.getAngle()) > 90 - L_FEATURE_CORNER_ANGLE_TOLERANCE)
				{
					return true;
				}
			}
		}
	}	
	return false;
}

Pattern* PatternManager::getEntryPattern()
{
	return &_enterPattern;
}

Pattern* PatternManager::getExitPattern()
{
	return &_exitPattern;
}

bool PatternManager::isSetup()
{
	return _setup;
}