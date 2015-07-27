#ifndef ModemStatusResponse_h
#define ModemStatusResponse_h

#include "XBeeResponse.h"
#include <inttypes.h>

/**
* Represents a Modem Status RX packet
*/
class ModemStatusResponse : public XBeeResponse {
public:
	ModemStatusResponse();
	uint8_t getStatus();
};


#endif