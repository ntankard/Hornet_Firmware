#ifndef FrameIdResponse_h
#define FrameIdResponse_h

#include "XBeeResponse.h"
#include <inttypes.h>

/**
* This class is extended by all Responses that include a frame id
*/
class FrameIdResponse : public XBeeResponse {
public:
	FrameIdResponse();
	uint8_t getFrameId();
private:
	uint8_t _frameId;
};

#endif