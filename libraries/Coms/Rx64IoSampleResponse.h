#ifndef Rx64IoSampleResponse_h
#define Rx64IoSampleResponse_h

#include "RxIoSampleBaseResponse.h"
#include "XBeeAddress64.h"
#include <inttypes.h>

class Rx64IoSampleResponse : public RxIoSampleBaseResponse {
public:
	Rx64IoSampleResponse();
	XBeeAddress64& getRemoteAddress64();
	uint8_t getRssiOffset();
private:
	XBeeAddress64 _remoteAddress;
};


#endif