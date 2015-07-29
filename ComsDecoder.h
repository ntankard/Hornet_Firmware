#pragma once
#include <inttypes.h>
#include "HornetManager.h"

class ComsDecoder
{
public:
	ComsDecoder(HornetManager *theManager);
	void processMessage(uint8_t *data, uint8_t dataLength);
	void sendFailure();
	void receiveFailure();

private:
	HornetManager *_theManager;
};

