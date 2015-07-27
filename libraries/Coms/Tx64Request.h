#ifndef Tx64Request_h
#define Tx64Request_h

#include "PayloadRequest.h"
#include "XBeeAddress64.h"
#include <inttypes.h>

/**
* Represents a Series 1 TX packet that corresponds to Api Id: TX_64_REQUEST
*
* Be careful not to send a data array larger than the max packet size of your radio.
* This class does not perform any validation of packet size and there will be no indication
* if the packet is too large, other than you will not get a TX Status response.
* The datasheet says 100 bytes is the maximum, although that could change in future firmware.
*/
class Tx64Request : public PayloadRequest {
public:
	Tx64Request(XBeeAddress64 &addr64, uint8_t option, uint8_t *payload, uint8_t payloadLength, uint8_t frameId);
	/**
	* Creates a unicast Tx64Request with the ACK option and DEFAULT_FRAME_ID
	*/
	Tx64Request(XBeeAddress64 &addr64, uint8_t *payload, uint8_t payloadLength);
	/**
	* Creates a default instance of this class.  At a minimum you must specify
	* a payload, payload length and a destination address before sending this request.
	*/
	Tx64Request();
	XBeeAddress64& getAddress64();
	void setAddress64(XBeeAddress64& addr64);
	// TODO move option to superclass
	uint8_t getOption();
	void setOption(uint8_t option);
	uint8_t getFrameData(uint8_t pos);
	uint8_t getFrameDataLength();
private:
	XBeeAddress64 _addr64;
	uint8_t _option;
};

#endif