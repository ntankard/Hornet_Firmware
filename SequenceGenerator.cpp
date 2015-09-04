#include "SequenceGenerator.h"


SequenceGenerator::SequenceGenerator()
{
	_rate = 1000;
	_blinks = 0;
	_gapMultiplyer = 0;
}

void SequenceGenerator::set(unsigned long rate, int blinks, int gapMultiplyer)
{
	_rate = rate;
	_blinks = blinks;
	_gapMultiplyer = gapMultiplyer;
	reset();
}

bool SequenceGenerator::run()
{
	if (_blinks == 0)
	{
		return false;
	}
	else if (_blinks == 1)
	{
		return runBlink();
	}
	else
	{
		return runSequence();
	}
}

bool SequenceGenerator::runBlink()
{

}

bool SequenceGenerator::runSequence()
{

}

void SequenceGenerator::reset()
{

}
