#ifndef RxDataResponse_h
#define RxDataResponse_h

#include "XBeeResponse.h"
#include <inttypes.h>

/**
* Common functionality for both Series 1 and 2 data RX data packets
*/
class RxDataResponse : public XBeeResponse {
public:
	RxDataResponse();
	/**
	* Returns the specified index of the payload.  The index may be 0 to getDataLength() - 1
	* This method is deprecated; use uint8_t* getData()
	*/
	uint8_t getData(int index);
	/**
	* Returns the payload array.  This may be accessed from index 0 to getDataLength() - 1
	*/
	uint8_t* getData();
	/**
	* Returns the length of the payload
	*/
	virtual uint8_t getDataLength() = 0;
	/**
	* Returns the position in the frame data where the data begins
	*/
	virtual uint8_t getDataOffset() = 0;
};

#endif