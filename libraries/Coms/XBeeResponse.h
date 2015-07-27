#ifndef XBeeResponse_h
#define XBeeResponse_h

#include <inttypes.h>

/*#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#define SERIES_1
#define SERIES_2*/
/**
* The super class of all XBee responses (RX packets)
* Users should never attempt to create an instance of this class; instead
* create an instance of a subclass
* It is recommend to reuse subclasses to conserve memory
*/
class XBeeResponse {
public:
	//static const int MODEM_STATUS = 0x8a;
	/**
	* Default constructor
	*/
	XBeeResponse();
	/**
	* Returns Api Id of the response
	*/
	uint8_t getApiId();
	void setApiId(uint8_t apiId);
	/**
	* Returns the MSB length of the packet
	*/
	uint8_t getMsbLength();
	void setMsbLength(uint8_t msbLength);
	/**
	* Returns the LSB length of the packet
	*/
	uint8_t getLsbLength();
	void setLsbLength(uint8_t lsbLength);
	/**
	* Returns the packet checksum
	*/
	uint8_t getChecksum();
	void setChecksum(uint8_t checksum);
	/**
	* Returns the length of the frame data: all bytes after the api id, and prior to the checksum
	* Note up to release 0.1.2, this was incorrectly including the checksum in the length.
	*/
	uint8_t getFrameDataLength();
	void setFrameData(uint8_t* frameDataPtr);
	/**
	* Returns the buffer that contains the response.
	* Starts with byte that follows API ID and includes all bytes prior to the checksum
	* Length is specified by getFrameDataLength()
	* Note: Unlike Digi's definition of the frame data, this does not start with the API ID..
	* The reason for this is all responses include an API ID, whereas my frame data
	* includes only the API specific data.
	*/
	uint8_t* getFrameData();

	void setFrameLength(uint8_t frameLength);
	// to support future 65535 byte packets I guess
	/**
	* Returns the length of the packet
	*/
	uint16_t getPacketLength();
	/**
	* Resets the response to default values
	*/
	void reset();
	/**
	* Initializes the response
	*/
	void init();
//#ifdef SERIES_2
	/**
	* Call with instance of ZBTxStatusResponse class only if getApiId() == ZB_TX_STATUS_RESPONSE
	* to populate response
	*/
	void getZBTxStatusResponse(XBeeResponse &response);
	/**
	* Call with instance of ZBRxResponse class only if getApiId() == ZB_RX_RESPONSE
	* to populate response
	*/
	void getZBRxResponse(XBeeResponse &response);
	/**
	* Call with instance of ZBRxIoSampleResponse class only if getApiId() == ZB_IO_SAMPLE_RESPONSE
	* to populate response
	*/
	void getZBRxIoSampleResponse(XBeeResponse &response);
//#endif
//#ifdef SERIES_1
	/**
	* Call with instance of TxStatusResponse only if getApiId() == TX_STATUS_RESPONSE
	*/
	void getTxStatusResponse(XBeeResponse &response);
	/**
	* Call with instance of Rx16Response only if getApiId() == RX_16_RESPONSE
	*/
	void getRx16Response(XBeeResponse &response);
	/**
	* Call with instance of Rx64Response only if getApiId() == RX_64_RESPONSE
	*/
	void getRx64Response(XBeeResponse &response);
	/**
	* Call with instance of Rx16IoSampleResponse only if getApiId() == RX_16_IO_RESPONSE
	*/
	void getRx16IoSampleResponse(XBeeResponse &response);
	/**
	* Call with instance of Rx64IoSampleResponse only if getApiId() == RX_64_IO_RESPONSE
	*/
	void getRx64IoSampleResponse(XBeeResponse &response);
//#endif
	/**
	* Call with instance of AtCommandResponse only if getApiId() == AT_COMMAND_RESPONSE
	*/
	void getAtCommandResponse(XBeeResponse &responses);
	/**
	* Call with instance of RemoteAtCommandResponse only if getApiId() == REMOTE_AT_COMMAND_RESPONSE
	*/
	void getRemoteAtCommandResponse(XBeeResponse &response);
	/**
	* Call with instance of ModemStatusResponse only if getApiId() == MODEM_STATUS_RESPONSE
	*/
	void getModemStatusResponse(XBeeResponse &response);
	/**
	* Returns true if the response has been successfully parsed and is complete and ready for use
	*/
	bool isAvailable();
	void setAvailable(bool complete);
	/**
	* Returns true if the response contains errors
	*/
	bool isError();
	/**
	* Returns an error code, or zero, if successful.
	* Error codes include: CHECKSUM_FAILURE, PACKET_EXCEEDS_BYTE_ARRAY_LENGTH, UNEXPECTED_START_BYTE
	*/
	uint8_t getErrorCode();
	void setErrorCode(uint8_t errorCode);
protected:
	// pointer to frameData
	uint8_t* _frameDataPtr;
private:
	void setCommon(XBeeResponse &target);
	uint8_t _apiId;
	uint8_t _msbLength;
	uint8_t _lsbLength;
	uint8_t _checksum;
	uint8_t _frameLength;
	bool _complete;
	uint8_t _errorCode;
};


#endif