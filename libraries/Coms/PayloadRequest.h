#ifndef PayloadRequest_h
#define PayloadRequest_h

#include "XBeeRequest.h"
#include <inttypes.h>

/**
* All TX packets that support payloads extend this class
*/
class PayloadRequest : public XBeeRequest {
public:
	PayloadRequest(uint8_t apiId, uint8_t frameId, uint8_t *payload, uint8_t payloadLength);
	/**
	* Returns the payload of the packet, if not null
	*/
	uint8_t* getPayload();
	/**
	* Sets the payload array
	*/
	void setPayload(uint8_t* payloadPtr);
	/**
	* Returns the length of the payload array, as specified by the user.
	*/
	uint8_t getPayloadLength();
	/**
	* Sets the length of the payload to include in the request.  For example if the payload array
	* is 50 bytes and you only want the first 10 to be included in the packet, set the length to 10.
	* Length must be <= to the array length.
	*/
	void setPayloadLength(uint8_t payloadLength);
private:
	uint8_t* _payloadPtr;
	uint8_t _payloadLength;
};

#endif