#ifndef ZBRxIoSampleResponse_h
#define ZBRxIoSampleResponse_h

#include"ZBRxResponse.h"
#include <inttypes.h>

/**
* Represents a Series 2 RX I/O Sample packet
*/
class ZBRxIoSampleResponse : public ZBRxResponse {
public:
	ZBRxIoSampleResponse();
	bool containsAnalog();
	bool containsDigital();
	/**
	* Returns true if the pin is enabled
	*/
	bool isAnalogEnabled(uint8_t pin);
	/**
	* Returns true if the pin is enabled
	*/
	bool isDigitalEnabled(uint8_t pin);
	/**
	* Returns the 10-bit analog reading of the specified pin.
	* Valid pins include ADC:xxx.
	*/
	uint16_t getAnalog(uint8_t pin);
	/**
	* Returns true if the specified pin is high/on.
	* Valid pins include DIO:xxx.
	*/
	bool isDigitalOn(uint8_t pin);
	uint8_t getDigitalMaskMsb();
	uint8_t getDigitalMaskLsb();
	uint8_t getAnalogMask();
};


#endif


