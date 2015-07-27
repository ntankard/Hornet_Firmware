#ifndef ZBRxResponse_h
#define ZBRxResponse_h

#include "RxDataResponse.h"
#include <inttypes.h>
#include "XBeeAddress64.h"

/**
* Represents a Series 2 RX packet
*/
class ZBRxResponse : public RxDataResponse {
public:
	ZBRxResponse();
	XBeeAddress64& getRemoteAddress64();
	uint16_t getRemoteAddress16();
	uint8_t getOption();
	uint8_t getDataLength();
	// frame position where data starts
	uint8_t getDataOffset();
private:
	XBeeAddress64 _remoteAddress64;
};

#endif