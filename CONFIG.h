#pragma once
#include "APM_2_5_PINS.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define BOARD_TYPE_APM 1
#define BOARD_TYPE_MEGA 2
#define BOARD_TYPE_DUO 3
#define BOARD_TYPE_UNO 4

#define COM_MODE_SERIAL 1
#define COM_MODE_XBEE 2

#define ENABLED 1
#define DISABLED 2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// Pick wich board to use
#define BOARD_TYPE BOARD_TYPE_UNO

// Pick wich coms to use (XBEE not avalible for uno, will default to SERIAL)
#define COM_MODE COM_MODE_SERIAL

// Enable relevent systems (some will be automaticaly disabled for certain board)
#define ENABLE_ACC			DISABLED
#define ENABLE_LIDAR		DISABLED
#define ENABLE_INDICATOR	DISABLED

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if BOARD_TYPE == BOARD_TYPE_UNO
	//UNO overrride components that are not suported
	#define ENABLE_ACC			DISABLED
	#define ENABLE_LIDAR		DISABLED
	#define ENABLE_INDICATOR	DISABLED
	#define COM_MODE			COM_MODE_SERIAL
#endif

#if BOARD_TYPE == BOARD_TYPE_APM
	#define ENABLE_LIDAR		DISABLED
#endif

#if BOARD_TYPE == BOARD_TYPE_MEGA
	#define ENABLE_ACC			DISABLED
	#define ENABLE_INDICATOR	DISABLED
#endif

#if BOARD_TYPE == BOARD_TYPE_DUO
	#define ENABLE_ACC			DISABLED
	#define ENABLE_LIDAR		DISABLED
	#define ENABLE_INDICATOR	DISABLED
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ COMPONENTS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if ENABLE_ACC == DISABLED
	#if BOARD_TYPE == BOARD_TYPE_APM
		#define USE_MPU6000
	#endif
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- PIN SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if COM_MODE == COM_MODE_XBEE
	#define C_COMS_PORT Serial1
#endif
#if COM_MODE == COM_MODE_SERIAL
	#define C_COMS_PORT Serial
#endif

#if ENABLE_LIDAR == DISABLED
	#if BOARD_TYPE == BOARD_TYPE_APM
		#define C_LIDAR_MOTOCTL 3
		#define C_LIDAR_SERIAL Serial2
	#else
		#define C_LIDAR_MOTOCTL 3
		#define C_LIDAR_SERIAL Serial2
	#endif
#endif


//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ COMM CODES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_COMS_CODE_CONNECT_REQUEST 'a'
#define C_COMS_CODE_CONNECT_CONFIRM 'b'
#define C_COMS_CODE_RESET			'r'
#define C_COMS_CODE_THROTTLE		't'
#define C_COMS_CODE_ARM_DISARM		'd'
#define C_COMS_CODE_ACCGYRO			'g'
#define C_COMS_CODE_PITCH_ROLL		'p'
#define C_COMS_CODE_LIDAR_POINT		'l'
#define C_COMS_CODE_LIDAR_EOS1		'e'
#define C_COMS_CODE_LIDAR_EOS2		'f'

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- ERROR CODES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define E_ILLEGAL_ACCESS 1
#define E_STATE_ERROR 2

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


#define C_ERROR_BUFFER 100
#define C_LOGGER_ACC_RATE 10
#define C_CONNECT_PULSE_TIME 1000

#if COM_MODE == COM_MODE_XBEE
	#define C_COMS_BAUD_RATE 9600
	#define C_COMMS_BSTATION_ADDRESS 0x0000
	#define C_COMMS_MAX_RETRY 3
#endif 

#if COM_MODE == COM_MODE_SERIAL
	#define C_COMS_BAUD_RATE 9600
	#define C_COMS_BUFFER 100
#endif


#define C_STATE_INDICATE_CONNECT Indicator::MAGENTA,1,500
#define C_STATE_INDICATE_IDLE Indicator::PURPLE,2,100
#define C_STATE_INDICATE_FLIGHT Indicator::BLUE,2,100

#define C_ACC_CS ACC_CS

#define C_PITCH_ROLL_WINDOW_AVE_WIDTH 10

#define C_LOGGER_PITCH_ROLL_RATE 10


//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- LIDAR SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- COMM SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
