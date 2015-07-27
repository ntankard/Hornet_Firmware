#ifndef ZBTxStatusResponse_h
#define ZBTxStatusResponse_h

#include "FrameIdResponse.h"
#include <inttypes.h>

/**
* Represents a Series 2 TX status packet
*/
class ZBTxStatusResponse : public FrameIdResponse {
public:
	ZBTxStatusResponse();
	uint16_t getRemoteAddress();
	uint8_t getTxRetryCount();
	uint8_t getDeliveryStatus();
	uint8_t getDiscoveryStatus();
	bool isSuccess();
};


#endif


