#pragma once
#include "APM_2_5_PINS.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define BOARD_TYPE_APM 1
#define BOARD_TYPE_MEGA 2

// Pick wich board to use
#define BOARD_TYPE BOARD_TYPE_APM

// uncoment all the features to use (unavalible features are not shown under certain boards)
#if BOARD_TYPE == BOARD_TYPE_APM
	#define USE_ACC
	//#define USE_LIDAR
	#define USE_INDICATOR
#endif
#if BOARD_TYPE == BOARD_TYPE_MEGA
	#define USE_LIDAR
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- COMM SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define COM_MODE_SERIAL 1
#define COM_MODE_XBEE 2

// pick wich com system to use
#define COM_MODE COM_MODE_SERIAL

#if COM_MODE == COM_MODE_XBEE
	#define C_COMS_PORT Serial1
	#define C_COMS_BAUD_RATE 9600
	#define C_COMMS_BSTATION_ADDRESS 0x0000
	#define C_COMMS_MAX_RETRY 3
#endif 

#if COM_MODE == COM_MODE_SERIAL
	#define C_COMS_PORT Serial
	#define C_COMS_BAUD_RATE 9600
	#define C_COMS_BUFFER 100
#endif

#define C_COMS_CODE_CONNECT_REQUEST 'a'
#define C_COMS_CODE_CONNECT_CONFIRM 'b'
#define C_COMS_CODE_RESET 'r'
#define C_COMS_CODE_THROTTLE 't'
#define C_COMS_CODE_ARM_DISARM 'd'

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- ERROR SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 100

#define E_ILLEGAL_ACCESS 1
#define E_STATE_ERROR 2


//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_LOGGER_ACC_RATE 10

#define C_CONNECT_PULSE_TIME 1000

#define C_STATE_INDICATE_CONNECT Indicator::MAGENTA,1,500
#define C_STATE_INDICATE_IDLE Indicator::PURPLE,2,100
#define C_STATE_INDICATE_FLIGHT Indicator::BLUE,2,100

#define C_ACC_CS ACC_CS

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- LIDAR SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if BOARD_TYPE == BOARD_TYPE_APM
#define C_LIDAR_MOTOCTL 3
#define C_LIDAR_SERIAL Serial2
#endif

#if BOARD_TYPE == BOARD_TYPE_MEGA
#define C_LIDAR_MOTOCTL 3
#define C_LIDAR_SERIAL Serial2
#endif