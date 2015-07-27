#ifndef XBeeAddress64_h
#define XBeeAddress64_h

#include "XBeeAddress.h"
#include <inttypes.h>

/**
* Represents a 64-bit XBee Address
*/

class XBeeAddress64 : public XBeeAddress {
public:
	XBeeAddress64(uint32_t msb, uint32_t lsb);
	XBeeAddress64();
	uint32_t getMsb();
	uint32_t getLsb();
	void setMsb(uint32_t msb);
	void setLsb(uint32_t lsb);
	//bool operator==(XBeeAddress64 addr);
	//bool operator!=(XBeeAddress64 addr);
private:
	uint32_t _msb;
	uint32_t _lsb;
};

#endif