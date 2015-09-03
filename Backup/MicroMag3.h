#pragma once
#include "CONFIG.h"

#if ENABLE_MAG == ENABLED

#include "SPIManager.h"
#include <stdint.h>
#include "Error.h"
#include "TimeOut.h"

/**
* \brief	Driver for the MicroMag3 Device
*/
class MicroMag3
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	theSPIManager	The SPI bus to use for comunications
	* \param	theError		The shared error object
	*/
	MicroMag3(SPIManager *theSPIManager,Error *e);

	/**
	* \brief	This device need no init, so this function just checks the conection
	*
	* \return	Is the deveice avalible and configured corectly?
	*/
	bool init();

	/**
	* \brief	Takes a step in the read process
	*
	* \throw	E_HARDWARE_FAILURE	If the read times out
	*
	* \return	Is new data avalible?
	*/
	bool update();

	/**
	* \brief	Gets the last full set of valid data
	*
	* \param	data	A buffer to place the data (size of 3)
	*/
	void getData(int16_t *data);

private:

	/**
	* \brief	Writes a single command to the chip
	*
	* \param	command	The command to send
	*/
	void sendCommand(uint8_t command);

	/** \brief	The SPI but to read over */
	SPIManager *_SPIManager;

	/** \brief	Wich sensor are we currently reading */
	int _sensor;

	/** \brief	The read data */
	int16_t _lastValid[3];

	/** \brief	A timer to check if data is received from the device in time */
	TimeOut _lastRead;

	/** \brief	The shared error object (mimics exeptions in c++) */
	Error *_e;
};

#endif

