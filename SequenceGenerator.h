#pragma once
class SequenceGenerator
{
public:
	SequenceGenerator();
	void set(unsigned long rate, int blinks, int gapMultiplyer);
	bool run();

private:
	bool runBlink();
	bool runSequence();

	void reset();

	unsigned long _rate;
	int _blinks;
	int _gapMultiplyer;
};

