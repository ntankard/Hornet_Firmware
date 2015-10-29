#pragma once
#include <Arduino.h>

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define ENABLE	1
#define DISABLE 2

#define XBEE	1
#define SERIAL	2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define DEBUG_BUILD			ENABLE

#define ENABLE_INDICATOR	ENABLE
#define ENABLE_GYRO			ENABLE
#define	ENABLE_LIDAR		ENABLE

#define COM_MODE			XBEE

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if DEBUG_BUILD == ENABLE

#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define TP(message) Serial.println(message);

#else

#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)

#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ COMPONENTS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if ENABLE_INDICATOR == ENABLE
	//#define USE_DM_INDICATOR
	#define USE_RBG_INDICATOR
#endif

#if ENABLE_GYRO == ENABLE
	#define USE_GYRO
	#define USE_MPU6050
#endif

#if ENABLE_LIDAR == ENABLE
	#define  USE_LIDAR
#endif

#if COM_MODE == XBEE
	#define COM_SERIAL		XBEE_SERIAL
	#define C_COM_SEND_RATE 12
#endif
#if COM_MODE == SERIAL
	#define COM_SERIAL		Serial
	#define C_COM_SEND_RATE 1
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 10

#define L_LINE_OF_BEST_FIT 1
#define L_POINT_TO_POINT 2
#define L_END_TO_POINT 3
#define L_START_TO_POINT 4

//----------------------------------------Feature recognition values-----------------------------------------------------------
#define L_LINE_TO_LINE_OFFSET 5
#define L_POINTS_IN_PATTERN 10
#define L_PATTERNS_IN_CORNER_FEATURE 2
#define L_PATTERN_RANGE_IN_FEATURE 50
#define L_FEATURE_CORNER_ANGLE_TOLERANCE 5
#define L_PATTERNS_STORED 10
#define L_FEATURES_STORED 30
#define L_FEATURE_RANGE_TOLERANCE 5
#define L_FEATURE_LIFE 5
#define L_FEATURE_OCCURANCES 3
#define L_ANCHORS_STORED 10
#define L_PATTERN_DEFINITION L_LINE_OF_BEST_FIT

#define LA_MOUNT_OFFSET		60.0
#define LA_SAFTEY_RADIUS	1500.0
#define LA_MIN_RADIUS		500.0

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- ERROR CODES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define E_NULL_PTR			0x01
#define E_TIMEOUT			0x05
#define E_HARDWARE_FAILURE	0x06
#define E_INDEX_OUT_BOUNDS	0x07
#define E_BUFFER_OVERFLOW   0x08
#define E_BUS_FAIL			0x09
#define E_PACKET_CORRUPTION	0x0A

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- SCHEDULER SETTINS ------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// The build depends on there being this many threads and them being from 0 to C_SCHEDULER_THREAD_NUM -1 with no repeats
#define C_SCHEDULER_THREAD_NUM 5

// must be in required start order
#define C_SCHEDULER_INDICATOR_THREAD 0
#define C_SCHEDULER_COMENCODER_THREAD 1
#define C_SCHEDULER_GYRO_THREAD 2
#define C_SCHEDULER_FLIGHT_THREAD 3
#define C_SCHEDULER_LIDAR_THREAD 4

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- STATE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


#define INDICATOR_PRI	100
#define COM_PRI			1
#define GYRO_PRI		50
#define FLIGHT_PRI		30
#define LIDAR_PRI		1

//							____________|			  Thread Priority									|_______________________
//							| State		| INDICATOR		| COM EN	|GYRO		|FLIGHT		|LIDAR		| LIGHT	|BLINKS| RATE
//							----------------------------------------------------------------------------------------------------
#define ST_TO_CONNECT		Connect,	INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	0,		1,		1000
#define ST_TO_IDLE			Idle,		INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	1,		2,		250
#define ST_TO_TAKEOFF		TakeOff,	INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	3,		3,		100
#define ST_TO_FLIGHT		Flight,		INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	2,		1,		1000
#define ST_TO_LAND			Land,		INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	3,		4,		100
#define ST_TO_EMERGENCY		Emergency,	INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	3,		1,		1000
#define ST_TO_CRACH			Crash,		INDICATOR_PRI,	COM_PRI,	GYRO_PRI,	FLIGHT_PRI,	LIDAR_PRI,	3,		1,		1000

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

// RBG indicator
#define RBG_GREEN 53
#define RBG_RED 51
#define RBG_BLUE 49

// APM conections
#define C_APM_ROLL		10
#define C_APM_PITCH		11
#define C_APM_THROTTLE	12
#define C_APM_YAW		13

// Coms
#define XBEE_SERIAL		Serial1

// LIDAR
#define C_LIDAR_SERIAL	Serial2


//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- MESSAGE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// inbound
#define MB_INBOUND_COUNT	5		// must match the numebr of packets!!
#define MB_INBOUND_OFFSET	100		// must match the lowest ID

#define MB_JOY_XY			100
#define MB_JOY_THROTTLE		101
#define MB_JOY_Z			102
#define MB_ARM_DISARM		103
#define MB_AVOID			104

// outbound
#define MB_OUTBOUND_COUTN		6		// must match the numebr of packets!!
#define MB_OUTBOUND_OFFSET		1		// must match the lowest ID

#define MB_ROLL_PITCH_YAW		1
#define MB_STATUS				2
#define MB_LAST_LIDAR			3
#define MB_COMPENSATOR_VECTOR	4
#define MB_JOY_VECTOR			5
#define MB_TOTAL_VECTOR			6

