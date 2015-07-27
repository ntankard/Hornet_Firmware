#include "XBeeRequest.h"

XBeeRequest::XBeeRequest(uint8_t apiId, uint8_t frameId) {
	_apiId = apiId;
	_frameId = frameId;
}

void XBeeRequest::setFrameId(uint8_t frameId) {
	_frameId = frameId;
}

uint8_t XBeeRequest::getFrameId() {
	return _frameId;
}

uint8_t XBeeRequest::getApiId() {
	return _apiId;
}

void XBeeRequest::setApiId(uint8_t apiId) {
	_apiId = apiId;
}

//void XBeeRequest::reset() {
//	_frameId = DEFAULT_FRAME_ID;
//}

//uint8_t XBeeRequest::getPayloadOffset() {
//	return _payloadOffset;
//}
//
//uint8_t XBeeRequest::setPayloadOffset(uint8_t payloadOffset) {
//	_payloadOffset = payloadOffset;
//}