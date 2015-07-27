#include "Rx16Response.h"
#include "XBee_Registers.h"

uint16_t Rx16Response::getRemoteAddress16() {
	return (getFrameData()[0] << 8) + getFrameData()[1];
}



Rx16Response::Rx16Response() : RxResponse() {

}

uint8_t Rx16Response::getRssiOffset() {
	return RX_16_RSSI_OFFSET;
}