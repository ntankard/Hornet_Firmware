#pragma once
#include <Arduino.h>

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define ENABLE	1
#define DISABLE 2


//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define DEBUG_BUILD ENABLE

#define ENABLE_INDICATOR	ENABLE
#define ENABLE_GYRO			ENABLE

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if DEBUG_BUILD == ENABLE

#define DEBUG_PRINT(x) Serial.print(x)
//#define DEBUG_PRINTF(x, y) Serial.print('d'+x, y)
#define DEBUG_PRINTLN(x) Serial.println(x)
//#define DEBUG_PRINTLNF(x, y) Serial.println('d'+x, y)
#define TP(message) Serial.println(message);

#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTF(x, y)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLNF(x, y)
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ COMPONENTS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if ENABLE_INDICATOR == ENABLE
#define USE_DM_INDICATOR
#endif

#if ENABLE_GYRO == ENABLE
#define USE_GYRO
#define USE_MPU6050
#endif

#define USER_SERIAL_COMS

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 10
#define C_COMS_BUFFER 10
#define C_COMS_PORT Serial
#define C_COMENCODER_SIZE 10
#define C_COMENCODER_M_SIZE 20
#define C_CONNECT_PULSE_TIME 1000


//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- ERROR CODES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define E_NULL_PTR			0x01
#define E_TIMEOUT			0x05
#define E_HARDWARE_FAILURE	0x06
#define E_INDEX_OUT_BOUNDS	0x07
#define E_BUFFER_OVERFLOW   0x08
#define E_BUS_FAIL			0x09

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- SCHEDULER SETTINS ------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// THe build depends on there being this many threads and them being from 0 to C_SCHEDULER_THREAD_NUM -1 with no repeats
#define C_SCHEDULER_THREAD_NUM 3

// must be in required start order
#define C_SCHEDULER_INDICATOR_THREAD 0
#define C_SCHEDULER_COMENCODER_THREAD 1
#define C_SCHEDULER_GYRO_THREAD 2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- STATE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


//							____________|			  Thread Priority		|_______________________
//							| State		| INDICATOR		| COM EN	|GYRO	| LIGHT	|BLINKS| RATE
//							-----------------------------------------------------------------
#define ST_TO_CONNECT		Connect,	10,				1,			0,		0,		1,		1000
#define ST_TO_IDLE			Idle,		10,				1,			5,		5,		2,		250
#define ST_TO_TAKEOFF		TakeOff,	10,				1,			5,		10,		3,		500
#define ST_TO_FLIGHT		Flight,		10,				1,			5,		15,		1,		1000
#define ST_TO_LAND			Land,		10,				1,			5,		20,		1,		1000
#define ST_TO_EMERGENCY		Emergency,	10,				1,			5,		21,		1,		1000
#define ST_TO_CRACH			Crash,		10,				1,			5,		22,		1,		1000

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- PIN SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// dot matrix
#define CANODE_1 A6
#define CANODE_2 A5
#define CANODE_3 A4
#define CANODE_4 A3
#define CANODE_5 A2
#define CANODE_6 A1
#define CANODE_7 A0
#define CANODE_8 9
#define CANODE_9 8
#define CANODE_10 7
#define CANODE_11 6
#define CANODE_12 5
#define CANODE_13 49
#define CANODE_14 47

// mag
#define C_MAG_SSNOT 10
#define C_MAG_DRDY 11
#define C_MAG_RESET 12

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- MESSAGE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// outbound	 com IDS
#define MB_ROLL_PITCH_YAW	'y'
#define MB_STATUS			's'
#define MB_MOTOR			'm'

// inbound coms IDS
#define MB_JOY_XY			'j'
#define MB_JOY_THROTTLE		't'
#define MB_JOY_Z			'z'

// com priorities
#define C_CL			6
#define C_CL_COMS		0
#define C_CL_SYSTEM_CMD 1
#define C_CL_NAV_CMD	2
#define C_CL_NAV_INFO	3
#define C_CL_NAV_USE	4
#define C_CL_DEBUG		5

// removed
#define C_COMS_CODE_CONNECT_REQUEST 'a'
#define C_COMS_CODE_CONNECT_CONFIRM 'b'



//									_________________________________________________________________
//									| ID				| SIZE	| MONITOR	| COM PRI		| BUFFER SIZE
//									-----------------------------------------------------------------
#define MB_ROLL_PITCH_YAW_SETTINGS	MB_ROLL_PITCH_YAW,	3,		10,			C_CL_NAV_INFO,	10
#define MB_STATUS_SETTINGS			MB_STATUS,			1,		1,			C_CL_SYSTEM_CMD,3
#define	MB_JOY_XY_SETTING			MB_JOY_XY,			2,		0,			C_CL_NAV_CMD,	1
#define	MB_JOY_THROTTLE_SETTING		MB_JOY_THROTTLE,	1,		0,			C_CL_NAV_CMD,	1
#define	MB_JOY_Z_SETTING			MB_JOY_Z,			1,		0,			C_CL_NAV_CMD,	1
#define	MB_MOTOR_SETTING			MB_MOTOR,			4,		1,			C_CL_NAV_INFO,	20

