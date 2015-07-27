#include"ZBRxIoSampleResponse.h"

ZBRxIoSampleResponse::ZBRxIoSampleResponse() : ZBRxResponse() {

}

// 64 + 16 addresses, sample size, option = 12 (index 11), so this starts at 12
uint8_t ZBRxIoSampleResponse::getDigitalMaskMsb() {
	return getFrameData()[12] & 0x1c;
}

uint8_t ZBRxIoSampleResponse::getDigitalMaskLsb() {
	return getFrameData()[13];
}

uint8_t ZBRxIoSampleResponse::getAnalogMask() {
	return getFrameData()[14] & 0x8f;
}

bool ZBRxIoSampleResponse::containsAnalog() {
	return getAnalogMask() > 0;
}

bool ZBRxIoSampleResponse::containsDigital() {
	return getDigitalMaskMsb() > 0 || getDigitalMaskLsb() > 0;
}

bool ZBRxIoSampleResponse::isAnalogEnabled(uint8_t pin) {
	return ((getAnalogMask() >> pin) & 1) == 1;
}

bool ZBRxIoSampleResponse::isDigitalEnabled(uint8_t pin) {
	if (pin <= 7) {
		// added extra parens to calm avr compiler
		return ((getDigitalMaskLsb() >> pin) & 1) == 1;
	}
	else {
		return ((getDigitalMaskMsb() >> (pin - 8)) & 1) == 1;
	}
}

uint16_t ZBRxIoSampleResponse::getAnalog(uint8_t pin) {
	// analog starts 13 bytes after sample size, if no dio enabled
	uint8_t start = 15;

	if (containsDigital()) {
		// make room for digital i/o
		start += 2;
	}

	//	std::cout << "spacing is " << static_cast<unsigned int>(spacing) << std::endl;

	// start depends on how many pins before this pin are enabled
	for (int i = 0; i < pin; i++) {
		if (isAnalogEnabled(i)) {
			start += 2;
		}
	}

	//	std::cout << "start for analog pin ["<< static_cast<unsigned int>(pin) << "]/sample " << static_cast<unsigned int>(sample) << " is " << static_cast<unsigned int>(start) << std::endl;

	//	std::cout << "returning index " << static_cast<unsigned int>(getSampleOffset() + start) << " and index " <<  static_cast<unsigned int>(getSampleOffset() + start + 1) << ", val is " << static_cast<unsigned int>(getFrameData()[getSampleOffset() + start] << 8) <<  " and " <<  + static_cast<unsigned int>(getFrameData()[getSampleOffset() + start + 1]) << std::endl;

	return (uint16_t)((getFrameData()[start] << 8) + getFrameData()[start + 1]);
}

bool ZBRxIoSampleResponse::isDigitalOn(uint8_t pin) {
	if (pin <= 7) {
		// D0-7
		// DIO LSB is index 5
		return ((getFrameData()[16] >> pin) & 1) == 1;
	}
	else {
		// D10-12
		// DIO MSB is index 4
		return ((getFrameData()[15] >> (pin - 8)) & 1) == 1;
	}
}