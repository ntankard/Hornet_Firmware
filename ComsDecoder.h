#pragma once
#include <inttypes.h>

class ComsDecoder
{
public:
	ComsDecoder();
	static void processMessage(uint8_t *data, uint8_t dataLength);
	static void sendFailure();
	static void receiveFailure();
};

