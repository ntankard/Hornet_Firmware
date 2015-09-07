#pragma once
#include "CONFIG.h"

#if ENABLE_ACC == ENABLED

#include "I2CManager.h"
//#include "SPIManager.h"
#include "Error.h"
#include <stdint.h>

/**
* \brief	The data packet from the MPU devices. Raw bytes are mapped to there float conterparts
*/
typedef union MPU60xx_Data_Packet
{
	struct
	{
		uint8_t x_accel_h;
		uint8_t x_accel_l;
		uint8_t y_accel_h;
		uint8_t y_accel_l;
		uint8_t z_accel_h;
		uint8_t z_accel_l;
		uint8_t t_h;
		uint8_t t_l;
		uint8_t x_gyro_h;
		uint8_t x_gyro_l;
		uint8_t y_gyro_h;
		uint8_t y_gyro_l;
		uint8_t z_gyro_h;
		uint8_t z_gyro_l;
	} reg;
	struct
	{
		int16_t x_accel;
		int16_t y_accel;
		int16_t z_accel;
		int16_t temperature;
		int16_t x_gyro;
		int16_t y_gyro;
		int16_t z_gyro;
	} value;
};

/**
* \brief	Driver for the MPU60xx series of 6 axis Acc and Gyro (compadible with I2C bus and SPI bus)
*/
class AP_InertialSensor_MPU600xx
{
public:

	/**
	* \brief	Constuctor for the I2C Bus
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \param	theI2CManager	The wrapper for the I2C Bus
	*/
	AP_InertialSensor_MPU600xx(volatile Error *e);

	/**
	* \brief	Sets up the Acc component
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \return	true the device could be setup, false if anything went wrong
	*
	* \throw   E_BUS_FAIL    If bus failed to read or write (will return false as well)
	*/
	bool init();

	/**
	* \brief	Gets new data from the MPU60xx if its avalible
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \return	true if new data is avalible
	*
	* \throw   E_BUS_FAIL    If bus failed to read or write (will return false as well)
	*/
	bool update();

	/**
	* \brief	Gets the last acc data.
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \param	gyro	A buffer to place the data
	*/
	void get_accels(int16_t* accel);

	/**
	* \brief	Gets the last gyro data.
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \param	gyro	A buffer to place the data
	*/
	void get_gyros(int16_t* gyro);

private:

	/**
	* \brief	Writes a single byte of data to the MPU
	*
	* \param	reg		The address to write to
	* \param	val		The data to write
	*
	* \throw   E_BUS_FAIL    If the write fails
	*/
	void register_write(uint8_t reg, uint8_t val);

	/**
	* \brief	Reads a single byte of data from the MPU
	*
	* \param	reg		The address to read from
	*
	* \throw   E_BUS_FAIL    If the write fails
	*
	* \return The read data
	*/
	uint8_t register_read(uint8_t reg);

	/**
	* \brief	Reads the full data set from the MPU and processes it
	*
	* \throw   E_BUS_FAIL    If the write fails
	*/
	void getData();

	/** \brief	The shared error object */
	volatile Error *_e;

	/** \brief	The bus object (SPI or I2C) */
	I2CManager _bus;

	/** \brief	The address of the bus object (chip select pit or I2C address) */
	uint8_t _address;

	/** \brief	Last valid data */
	MPU60xx_Data_Packet _data;
};

#endif

