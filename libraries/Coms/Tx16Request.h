#ifndef Tx16Request_h
#define Tx16Request_h

#include "PayloadRequest.h"
#include <inttypes.h>

/**
* Represents a Series 1 TX packet that corresponds to Api Id: TX_16_REQUEST
* <p/>
* Be careful not to send a data array larger than the max packet size of your radio.
* This class does not perform any validation of packet size and there will be no indication
* if the packet is too large, other than you will not get a TX Status response.
* The datasheet says 100 bytes is the maximum, although that could change in future firmware.
*/
class Tx16Request : public PayloadRequest {
public:
	Tx16Request(uint16_t addr16, uint8_t option, uint8_t *payload, uint8_t payloadLength, uint8_t frameId);
	/**
	* Creates a Unicast Tx16Request with the ACK option and DEFAULT_FRAME_ID
	*/
	Tx16Request(uint16_t addr16, uint8_t *payload, uint8_t payloadLength);
	/**
	* Creates a default instance of this class.  At a minimum you must specify
	* a payload, payload length and a destination address before sending this request.
	*/
	Tx16Request();
	uint16_t getAddress16();
	void setAddress16(uint16_t addr16);
	uint8_t getOption();
	void setOption(uint8_t option);
	uint8_t getFrameData(uint8_t pos);
	uint8_t getFrameDataLength();
protected:
private:
	uint16_t _addr16;
	uint8_t _option;
};

#endif