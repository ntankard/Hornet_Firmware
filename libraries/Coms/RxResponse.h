#ifndef RxResponse_h
#define RxResponse_h

#include "RxDataResponse.h"
#include <inttypes.h>

/**
* Represents a Series 1 RX packet
*/
class RxResponse : public RxDataResponse {
public:
	RxResponse();
	// remember rssi is negative but this is unsigned byte so it's up to you to convert
	uint8_t getRssi();
	uint8_t getOption();
	bool isAddressBroadcast();
	bool isPanBroadcast();
	uint8_t getDataLength();
	uint8_t getDataOffset();
	virtual uint8_t getRssiOffset() = 0;
};

#endif