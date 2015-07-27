#ifndef XBeeRequest_h
#define XBeeRequest_h

#include <inttypes.h>

/**
* Super class of all XBee requests (TX packets)
* Users should never create an instance of this class; instead use an subclass of this class
* It is recommended to reuse Subclasses of the class to conserve memory
* <p/>
* This class allocates a buffer to
*/
class XBeeRequest {
public:
	/**
	* Constructor
	* TODO make protected
	*/
	XBeeRequest(uint8_t apiId, uint8_t frameId);
	/**
	* Sets the frame id.  Must be between 1 and 255 inclusive to get a TX status response.
	*/
	void setFrameId(uint8_t frameId);
	/**
	* Returns the frame id
	*/
	uint8_t getFrameId();
	/**
	* Returns the API id
	*/
	uint8_t getApiId();
	// setting = 0 makes this a pure virtual function, meaning the subclass must implement, like abstract in java
	/**
	* Starting after the frame id (pos = 0) and up to but not including the checksum
	* Note: Unlike Digi's definition of the frame data, this does not start with the API ID.
	* The reason for this is the API ID and Frame ID are common to all requests, whereas my definition of
	* frame data is only the API specific data.
	*/
	virtual uint8_t getFrameData(uint8_t pos) = 0;
	/**
	* Returns the size of the api frame (not including frame id or api id or checksum).
	*/
	virtual uint8_t getFrameDataLength() = 0;
	//void reset();
protected:
	void setApiId(uint8_t apiId);
private:
	uint8_t _apiId;
	uint8_t _frameId;
};

#endif