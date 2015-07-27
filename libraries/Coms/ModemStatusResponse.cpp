#include "ModemStatusResponse.h"

ModemStatusResponse::ModemStatusResponse() {

}

uint8_t ModemStatusResponse::getStatus() {
	return getFrameData()[0];
}