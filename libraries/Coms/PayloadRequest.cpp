#include "PayloadRequest.h"

PayloadRequest::PayloadRequest(uint8_t apiId, uint8_t frameId, uint8_t *payload, uint8_t payloadLength) : XBeeRequest(apiId, frameId) {
	_payloadPtr = payload;
	_payloadLength = payloadLength;
}

uint8_t* PayloadRequest::getPayload() {
	return _payloadPtr;
}

void PayloadRequest::setPayload(uint8_t* payload) {
	_payloadPtr = payload;
}

uint8_t PayloadRequest::getPayloadLength() {
	return _payloadLength;
}

void PayloadRequest::setPayloadLength(uint8_t payloadLength) {
	_payloadLength = payloadLength;
}
