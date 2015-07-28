#pragma once
#include <inttypes.h>
#include "HornetManager.h"

class ComsDecoder
{
public:
	ComsDecoder(HornetManager *theManager);
	static void processMessage(uint8_t *data, uint8_t dataLength);
	static void sendFailure();
	static void receiveFailure();
private:
	HornetManager *_theManager;
};

