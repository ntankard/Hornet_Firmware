#ifndef Rx64Response_h
#define Rx64Response_h

#include "RxResponse.h"
#include "XBeeAddress64.h"
#include <inttypes.h>

/**
* Represents a Series 1 64-bit address RX packet
*/
class Rx64Response : public RxResponse {
public:
	Rx64Response();
	uint8_t getRssiOffset();
	XBeeAddress64& getRemoteAddress64();
private:
	XBeeAddress64 _remoteAddress;
};

#endif