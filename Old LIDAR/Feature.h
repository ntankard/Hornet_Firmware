#pragma once 
#include "Arduino.h"
#include "Pattern.h"
#include "CONFIG.h"

enum FeatureState { FEATURE_HEAD, FEATURE_TAIL, FEATURE_NULL, FEATURE_DATA };

class Feature
{
public:
	Feature()
	{
		_state = FEATURE_NULL;
		_enter_start_coorX = 0;
		_enter_start_coorY = 0;
		_enter_end_coorX = 0;
		_enter_end_coorY = 0;

		_exit_start_coorX = 0;
		_exit_start_coorY = 0;
		_exit_end_coorX = 0;
		_exit_end_coorY = 0;

		_life = 0;
		_occurances = 0;
	}

	void setFeature(Pattern* enterPattern, Pattern* exitPattern)
	{
		_state = FEATURE_DATA;

		_enter_start_coorX = enterPattern->getStartCoordX();
		_enter_start_coorY = enterPattern->getStartCoordY();
		_enter_end_coorX = enterPattern->getEndCoordX();
		_enter_end_coorY = enterPattern->getEndCoordY();

		_exit_start_coorX = exitPattern->getStartCoordX();
		_exit_start_coorY = exitPattern->getStartCoordY();
		_exit_end_coorX = exitPattern->getEndCoordX();
		_exit_end_coorY = exitPattern->getEndCoordY();

		_life = L_FEATURE_LIFE;
		_occurances = 0;
	}

	void updateOccurances()
	{
		_occurances++;
	}

	int getOccurances()
	{
		return _occurances;
	}

	FeatureState getState()
	{
		return _state;
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
		return _exit_start_coorY;
	}

	float getExitEndX()
	{
		return _exit_end_coorX;
	}

	float getExitEndY()
	{
		return _exit_end_coorY;
	}

	void loseLife()
	{
		_life--;
	}

	void setLife(int life)
	{
		_life = life;
	}

	int getLife()
	{
		return _life;
	}

	void setState(FeatureState state)
	{
		_state = state;
	}

private:
	FeatureState _state;

	float _enter_start_coorX;
	float _enter_start_coorY;
	float _enter_end_coorX;
	float _enter_end_coorY;

	float _exit_start_coorX;
	float _exit_start_coorY;
	float _exit_end_coorX;
	float _exit_end_coorY;

	int _life;
	int _occurances;
};