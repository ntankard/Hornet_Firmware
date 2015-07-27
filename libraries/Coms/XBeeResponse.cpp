#include "XBeeResponse.h"
#include "XBee_Registers.h"
#include "TxStatusResponse.h"
#include "ZBTxStatusResponse.h"
#include "ZBRxResponse.h"
#include "ZBRxIoSampleResponse.h"
#include "Rx16IoSampleResponse.h"
#include "Rx64IoSampleResponse.h"
#include "Rx64Response.h"
#include "RemoteAtCommandResponse.h"
#include "ModemStatusResponse.h"
#include "Rx16Response.h"
XBeeResponse::XBeeResponse() {

}

uint8_t XBeeResponse::getApiId() {
	return _apiId;
}

void XBeeResponse::setApiId(uint8_t apiId) {
	_apiId = apiId;
}

uint8_t XBeeResponse::getMsbLength() {
	return _msbLength;
}

void XBeeResponse::setMsbLength(uint8_t msbLength) {
	_msbLength = msbLength;
}

uint8_t XBeeResponse::getLsbLength() {
	return _lsbLength;
}

void XBeeResponse::setLsbLength(uint8_t lsbLength) {
	_lsbLength = lsbLength;
}

uint8_t XBeeResponse::getChecksum() {
	return _checksum;
}

void XBeeResponse::setChecksum(uint8_t checksum) {
	_checksum = checksum;
}

uint8_t XBeeResponse::getFrameDataLength() {
	return _frameLength;
}

void XBeeResponse::setFrameLength(uint8_t frameLength) {
	_frameLength = frameLength;
}

bool XBeeResponse::isAvailable() {
	return _complete;
}

void XBeeResponse::setAvailable(bool complete) {
	_complete = complete;
}

bool XBeeResponse::isError() {
	return _errorCode > 0;
}

uint8_t XBeeResponse::getErrorCode() {
	return _errorCode;
}

void XBeeResponse::setErrorCode(uint8_t errorCode) {
	_errorCode = errorCode;
}

// copy common fields from xbee response to target response
void XBeeResponse::setCommon(XBeeResponse &target) {
	target.setApiId(getApiId());
	target.setAvailable(isAvailable());
	target.setChecksum(getChecksum());
	target.setErrorCode(getErrorCode());
	target.setFrameLength(getFrameDataLength());
	target.setMsbLength(getMsbLength());
	target.setLsbLength(getLsbLength());
}

void XBeeResponse::getZBTxStatusResponse(XBeeResponse &zbXBeeResponse) {

	// way off?
	ZBTxStatusResponse* zb = static_cast<ZBTxStatusResponse*>(&zbXBeeResponse);
	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(zbXBeeResponse);
}



void XBeeResponse::getZBRxResponse(XBeeResponse &rxResponse) {

	ZBRxResponse* zb = static_cast<ZBRxResponse*>(&rxResponse);

	//TODO verify response api id matches this api for this response

	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(rxResponse);

	zb->getRemoteAddress64().setMsb((uint32_t(getFrameData()[0]) << 24) + (uint32_t(getFrameData()[1]) << 16) + (uint16_t(getFrameData()[2]) << 8) + getFrameData()[3]);
	zb->getRemoteAddress64().setLsb((uint32_t(getFrameData()[4]) << 24) + (uint32_t(getFrameData()[5]) << 16) + (uint16_t(getFrameData()[6]) << 8) + (getFrameData()[7]));
}

void XBeeResponse::getZBRxIoSampleResponse(XBeeResponse &response) {
	ZBRxIoSampleResponse* zb = static_cast<ZBRxIoSampleResponse*>(&response);


	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(response);

	zb->getRemoteAddress64().setMsb((uint32_t(getFrameData()[0]) << 24) + (uint32_t(getFrameData()[1]) << 16) + (uint16_t(getFrameData()[2]) << 8) + getFrameData()[3]);
	zb->getRemoteAddress64().setLsb((uint32_t(getFrameData()[4]) << 24) + (uint32_t(getFrameData()[5]) << 16) + (uint16_t(getFrameData()[6]) << 8) + (getFrameData()[7]));
}

void XBeeResponse::getRx16IoSampleResponse(XBeeResponse &response) {
	Rx16IoSampleResponse* rx = static_cast<Rx16IoSampleResponse*>(&response);

	rx->setFrameData(getFrameData());
	setCommon(response);
}




void XBeeResponse::getRx64IoSampleResponse(XBeeResponse &response) {
	Rx64IoSampleResponse* rx = static_cast<Rx64IoSampleResponse*>(&response);

	rx->setFrameData(getFrameData());
	setCommon(response);

	rx->getRemoteAddress64().setMsb((uint32_t(getFrameData()[0]) << 24) + (uint32_t(getFrameData()[1]) << 16) + (uint16_t(getFrameData()[2]) << 8) + getFrameData()[3]);
	rx->getRemoteAddress64().setLsb((uint32_t(getFrameData()[4]) << 24) + (uint32_t(getFrameData()[5]) << 16) + (uint16_t(getFrameData()[6]) << 8) + getFrameData()[7]);
}



void XBeeResponse::getTxStatusResponse(XBeeResponse &txResponse) {

	TxStatusResponse* txStatus = static_cast<TxStatusResponse*>(&txResponse);

	// pass pointer array to subclass
	txStatus->setFrameData(getFrameData());
	setCommon(txResponse);
}

void XBeeResponse::getRx64Response(XBeeResponse &rx64Response) {

	Rx64Response* rx64 = static_cast<Rx64Response*>(&rx64Response);

	// pass pointer array to subclass
	rx64->setFrameData(getFrameData());
	setCommon(rx64Response);

	rx64->getRemoteAddress64().setMsb((uint32_t(getFrameData()[0]) << 24) + (uint32_t(getFrameData()[1]) << 16) + (uint16_t(getFrameData()[2]) << 8) + getFrameData()[3]);
	rx64->getRemoteAddress64().setLsb((uint32_t(getFrameData()[4]) << 24) + (uint32_t(getFrameData()[5]) << 16) + (uint16_t(getFrameData()[6]) << 8) + getFrameData()[7]);
}




void XBeeResponse::getRemoteAtCommandResponse(XBeeResponse &response) {

	// TODO no real need to cast.  change arg to match expected class
	RemoteAtCommandResponse* at = static_cast<RemoteAtCommandResponse*>(&response);

	// pass pointer array to subclass
	at->setFrameData(getFrameData());
	setCommon(response);

	at->getRemoteAddress64().setMsb((uint32_t(getFrameData()[1]) << 24) + (uint32_t(getFrameData()[2]) << 16) + (uint16_t(getFrameData()[3]) << 8) + getFrameData()[4]);
	at->getRemoteAddress64().setLsb((uint32_t(getFrameData()[5]) << 24) + (uint32_t(getFrameData()[6]) << 16) + (uint16_t(getFrameData()[7]) << 8) + (getFrameData()[8]));

}







void XBeeResponse::getModemStatusResponse(XBeeResponse &modemStatusResponse) {

	ModemStatusResponse* modem = static_cast<ModemStatusResponse*>(&modemStatusResponse);

	// pass pointer array to subclass
	modem->setFrameData(getFrameData());
	setCommon(modemStatusResponse);

}



void XBeeResponse::getAtCommandResponse(XBeeResponse &atCommandResponse) {

	AtCommandResponse* at = static_cast<AtCommandResponse*>(&atCommandResponse);

	// pass pointer array to subclass
	at->setFrameData(getFrameData());
	setCommon(atCommandResponse);
}

uint16_t XBeeResponse::getPacketLength() {
	return ((_msbLength << 8) & 0xff) + (_lsbLength & 0xff);
}

uint8_t* XBeeResponse::getFrameData() {
	return _frameDataPtr;
}

void XBeeResponse::setFrameData(uint8_t* frameDataPtr) {
	_frameDataPtr = frameDataPtr;
}

void XBeeResponse::init() {
	_complete = false;
	_errorCode = NO_ERROR;
	_checksum = 0;
}

void XBeeResponse::reset() {
	init();
	_apiId = 0;
	_msbLength = 0;
	_lsbLength = 0;
	_checksum = 0;
	_frameLength = 0;

	_errorCode = NO_ERROR;
}

void XBeeResponse::getRx16Response(XBeeResponse &rx16Response) {

	Rx16Response* rx16 = static_cast<Rx16Response*>(&rx16Response);

	// pass pointer array to subclass
	rx16->setFrameData(getFrameData());
	setCommon(rx16Response);

	//	rx16->getRemoteAddress16().setAddress((getFrameData()[0] << 8) + getFrameData()[1]);
}