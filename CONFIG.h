#pragma once
#include "APM_2_5_PINS.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define BOARD_TYPE_APM 1
#define BOARD_TYPE_MEGA 2
#define BOARD_TYPE_DUO 3

#define COM_MODE_SERIAL 1
#define COM_MODE_XBEE 2

#define ENABLED 1
#define DISABLED 2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// Pick wich board to use
#define BOARD_TYPE BOARD_TYPE_APM

// Pick wich coms to use (XBEE not avalible for uno, will default to SERIAL)
#define COM_MODE COM_MODE_SERIAL

// Enable relevent systems (some will be automaticaly disabled for certain board)
#define ENABLE_ACC			ENABLED
#define ENABLE_LIDAR		DISABLED
#define ENABLE_INDICATOR	ENABLED

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// What features do the board suport?

#if BOARD_TYPE == BOARD_TYPE_APM
	#define ENABLE_LIDAR		DISABLED
#endif

#if BOARD_TYPE == BOARD_TYPE_MEGA
	#define ENABLE_LIDAR		DISABLED
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

// What componets do you use based on the Board type

#if ENABLE_ACC == ENABLED
	#if BOARD_TYPE == BOARD_TYPE_APM
		#define USE_MPU6000
	#else
		#define USE_MPU6050
	#endif
#endif

#if ENABLE_INDICATOR == ENABLED
	#if BOARD_TYPE == BOARD_TYPE_APM
		#define USE_APM_INDICATOR
	#else
		#define USE_DOT_MATRIX
	#endif
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- PIN SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if BOARD_TYPE == BOARD_TYPE_APM

	// indicator
	#define BLUE_LED APM_BLUE_LED
	#define YELLOY_LED APM_YELLOY_LED
	#define RED_LED APM_RED_LED

#else	// MEGA and DUO

	// dot matrix
	#define CANODE_1 A14
	#define CANODE_2 A13
	#define CANODE_3 A12
	#define CANODE_4 A11
	#define CANODE_5 A10
	#define CANODE_6 A9
	#define CANODE_7 A8
	#define CANODE_8 33
	#define CANODE_9 26
	#define CANODE_10 27
	#define CANODE_11 43
	#define CANODE_12 38
	#define CANODE_13 35
	#define CANODE_14 30
#endif


#if COM_MODE == COM_MODE_XBEE
	#define C_COMS_PORT Serial1
#endif
#if COM_MODE == COM_MODE_SERIAL
	#define C_COMS_PORT Serial
#endif

#if ENABLE_LIDAR == ENABLED
	#if BOARD_TYPE == BOARD_TYPE_APM
		#define C_LIDAR_MOTOCTL 3
		#define C_LIDAR_SERIAL Serial2
	#else
		#define C_LIDAR_MOTOCTL 3
		#define C_LIDAR_SERIAL Serial2
	#endif
#endif

#if ENABLE_ACC == ENABLED
	#ifdef USE_MPU6000
		#define MPU6000_CS ACC_CS // from APM
		#define MPU6000_INTERRUPT 6
	#endif
	#ifdef USE_MPU6050
		#define MPU6050_INTERRUPT 2
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
#define E_BUS_FAIL 3

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

//enum Color{ BLUE, YELLOW, RED, PURPLE, ORANGE, MAGENTA };

#define C_STATE_INDICATE_CONNECT 5,1,500
#define C_STATE_INDICATE_IDLE 3,2,100
#define C_STATE_INDICATE_FLIGHT 0,2,100

#define C_ACC_CS ACC_CS

#define C_PITCH_ROLL_WINDOW_AVE_WIDTH 10

#define C_LOGGER_PITCH_ROLL_RATE 10


//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- LIDAR SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- COMM SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
