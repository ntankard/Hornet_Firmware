#ifndef ZBTxRequest_h
#define ZBTxRequest_h

#include "PayloadRequest.h"
#include "XBeeAddress64.h"
#include <inttypes.h>

/**
* Represents a Series 2 TX packet that corresponds to Api Id: ZB_TX_REQUEST
*
* Be careful not to send a data array larger than the max packet size of your radio.
* This class does not perform any validation of packet size and there will be no indication
* if the packet is too large, other than you will not get a TX Status response.
* The datasheet says 72 bytes is the maximum for ZNet firmware and ZB Pro firmware provides
* the ATNP command to get the max supported payload size.  This command is useful since the
* maximum payload size varies according to certain settings, such as encryption.
* ZB Pro firmware provides a PAYLOAD_TOO_LARGE that is returned if payload size
* exceeds the maximum.
*/
class ZBTxRequest : public PayloadRequest {
public:
	/**
	* Creates a unicast ZBTxRequest with the ACK option and DEFAULT_FRAME_ID
	*/
	ZBTxRequest(XBeeAddress64 &addr64, uint8_t *payload, uint8_t payloadLength);
	ZBTxRequest(XBeeAddress64 &addr64, uint16_t addr16, uint8_t broadcastRadius, uint8_t option, uint8_t *payload, uint8_t payloadLength, uint8_t frameId);
	/**
	* Creates a default instance of this class.  At a minimum you must specify
	* a payload, payload length and a destination address before sending this request.
	*/
	ZBTxRequest();
	XBeeAddress64& getAddress64();
	uint16_t getAddress16();
	uint8_t getBroadcastRadius();
	uint8_t getOption();
	void setAddress64(XBeeAddress64& addr64);
	void setAddress16(uint16_t addr16);
	void setBroadcastRadius(uint8_t broadcastRadius);
	void setOption(uint8_t option);
protected:
	// declare virtual functions
	uint8_t getFrameData(uint8_t pos);
	uint8_t getFrameDataLength();
private:
	XBeeAddress64 _addr64;
	uint16_t _addr16;
	uint8_t _broadcastRadius;
	uint8_t _option;
};


#endif