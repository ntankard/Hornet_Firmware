#pragma once 
#include "Feature.h"
#include "CONFIG.h"

enum AnchorState { ANCHOR_HEAD, ANCHOR_TAIL, ANCHOR_NULL, ANCHOR_DATA };

class Anchor
{
public:
	Anchor()
	{
		_state = ANCHOR_NULL;
	}

	void setAnchor(Feature* recurringFeature)
	{
		_state = ANCHOR_DATA;

		_enter_start_coorX = recurringFeature->getEnterStartX();
		_enter_start_coorY = recurringFeature->getEnterStartY();
		_enter_end_coorX = recurringFeature->getEnterEndX();
		_enter_end_coorY = recurringFeature->getEnterEndY();

		_exit_start_coorX = recurringFeature->getExitStartX();
		_exit_start_coorY = recurringFeature->getExitStartY();
		_exit_end_coorX = recurringFeature->getExitEndX();
		_exit_end_coorY = recurringFeature->getExitEndY();
	}

	AnchorState getState()
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

	void setState(AnchorState state)
	{
		_state = state;
	}

private:
	AnchorState _state;

	float _enter_start_coorX;
	float _enter_start_coorY;
	float _enter_end_coorX;
	float _enter_end_coorY;

	float _exit_start_coorX;
	float _exit_start_coorY;
	float _exit_end_coorX;
	float _exit_end_coorY;
};