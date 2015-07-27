#include "TxStatusResponse.h"
#include "XBee_Registers.h"

TxStatusResponse::TxStatusResponse() : FrameIdResponse() {

}

uint8_t TxStatusResponse::getStatus() {
	return getFrameData()[1];
}

bool TxStatusResponse::isSuccess() {
	return getStatus() == SUCCESS;
}