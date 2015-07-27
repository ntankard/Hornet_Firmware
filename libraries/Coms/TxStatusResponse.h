#ifndef TxStatusResponse_h
#define TxStatusResponse_h

#include "FrameIdResponse.h"
#include <inttypes.h>

/**
* Represents a Series 1 TX Status packet
*/
class TxStatusResponse : public FrameIdResponse {
public:
	TxStatusResponse();
	uint8_t getStatus();
	bool isSuccess();
};

#endif