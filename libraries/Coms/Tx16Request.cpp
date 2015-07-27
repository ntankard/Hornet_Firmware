#include "Tx16Request.h"
#include "XBee_Registers.h"

Tx16Request::Tx16Request() : PayloadRequest(TX_16_REQUEST, DEFAULT_FRAME_ID, NULL, 0) {

}

Tx16Request::Tx16Request(uint16_t addr16, uint8_t option, uint8_t *data, uint8_t dataLength, uint8_t frameId) : PayloadRequest(TX_16_REQUEST, frameId, data, dataLength) {
	_addr16 = addr16;
	_option = option;
}

Tx16Request::Tx16Request(uint16_t addr16, uint8_t *data, uint8_t dataLength) : PayloadRequest(TX_16_REQUEST, DEFAULT_FRAME_ID, data, dataLength) {
	_addr16 = addr16;
	_option = ACK_OPTION;
}

uint8_t Tx16Request::getFrameData(uint8_t pos) {

	if (pos == 0) {
		return (_addr16 >> 8) & 0xff;
	}
	else if (pos == 1) {
		return _addr16 & 0xff;
	}
	else if (pos == 2) {
		return _option;
	}
	else {
		return getPayload()[pos - TX_16_API_LENGTH];
	}
}

uint8_t Tx16Request::getFrameDataLength() {
	return TX_16_API_LENGTH + getPayloadLength();
}

uint16_t Tx16Request::getAddress16() {
	return _addr16;
}

void Tx16Request::setAddress16(uint16_t addr16) {
	_addr16 = addr16;
}

uint8_t Tx16Request::getOption() {
	return _option;
}

void Tx16Request::setOption(uint8_t option) {
	_option = option;
}