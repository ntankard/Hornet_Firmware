#ifndef Rx16IoSampleResponse_h
#define Rx16IoSampleResponse_h

#include "RxIoSampleBaseResponse.h"
#include <inttypes.h>

class Rx16IoSampleResponse : public RxIoSampleBaseResponse {
public:
	Rx16IoSampleResponse();
	uint16_t getRemoteAddress16();
	uint8_t getRssiOffset();

};

#endif