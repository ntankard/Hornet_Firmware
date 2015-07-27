#ifndef Rx16Response_h
#define Rx16Response_h

#include "RxResponse.h"
#include <inttypes.h>

/**
* Represents a Series 1 16-bit address RX packet
*/
class Rx16Response : public RxResponse {
public:
	Rx16Response();
	uint8_t getRssiOffset();
	uint16_t getRemoteAddress16();
protected:
	uint16_t _remoteAddress;
};


#endif