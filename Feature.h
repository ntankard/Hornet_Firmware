#pragma once 
#include "Arduino.h"
#include "math.h"
#include "Pattern.h"

class Feature
{
public:
	Feature(Pattern* enterPattern, Pattern* exitPattern)
	{
		float _enter_start_coorX = enterPattern->getStartCoordX();
		float _enter_start_coorY = enterPattern->getStartCoordY();
		float _enter_end_coorX = enterPattern->getEndCoordX();
		float _enter_end_coorY = enterPattern->getEndCoordY();

		float _exit_start_coorX = exitPattern->getStartCoordX();
		float _exit_start_coorY = exitPattern->getStartCoordY();
		float _exit_end_coorX = exitPattern->getEndCoordX();
		float _exit_end_coorY = exitPattern->getEndCoordY();
	}

	float getEnterStartX()
	{
		return _enter_start_coorX;
	}

	float getEnterStartY()
	{
		return _enter_start_coorY;
	}

	float getEnterEndX()
	{
		return _enter_end_coorX;
	}

	float getEnterEndY()
	{
		return _enter_end_coorY;
	}

	float getExitStartX()
	{
		return _exit_start_coorX;
	}

	float getExitStartY()
	{
		return _exit_start_coorY
	}

	float getExitEndX()
	{
		return _exit_end_coorX;
	}

	float getExitEndY()
	{
		return _exit_end_coorY;
	}

private:
	float _enter_start_coorX;
	float _enter_start_coorY;
	float _enter_end_coorX;
	float _enter_end_coorY;

	float _exit_start_coorX;
	float _exit_start_coorY;
	float _exit_end_coorX;
	float _exit_end_coorY;
};