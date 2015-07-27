#include "ZBTxStatusResponse.h"
#include "XBee_Registers.h"

ZBTxStatusResponse::ZBTxStatusResponse() : FrameIdResponse() {

}

uint16_t ZBTxStatusResponse::getRemoteAddress() {
	return  (getFrameData()[1] << 8) + getFrameData()[2];
}

uint8_t ZBTxStatusResponse::getTxRetryCount() {
	return getFrameData()[3];
}

uint8_t ZBTxStatusResponse::getDeliveryStatus() {
	return getFrameData()[4];
}

uint8_t ZBTxStatusResponse::getDiscoveryStatus() {
	return getFrameData()[5];
}

bool ZBTxStatusResponse::isSuccess() {
	return getDeliveryStatus() == SUCCESS;
}