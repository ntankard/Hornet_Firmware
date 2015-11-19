#pragma once

#include "Arduino.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// do not change thease

#define ENABLE	1
#define DISABLE 2

#define XBEE	1
#define SERIAL	2

#define JOYSTICK	1
#define EXTERNAL	2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// If this is enabled debug statments and test statments will print
#define DEBUG_BUILD			ENABLE

// swich on or off any component in the system
#define ENABLE_INDICATOR	ENABLE
#define ENABLE_GYRO			ENABLE
#define	ENABLE_LIDAR		ENABLE

// is the systme conected via USB(SERIAL) or wirlesslee(XBEE)? (Needs to be in XBEE mode for remote flight)
#define COM_MODE			SERIAL

// is there an external receiver attached to the system?
#define FLIGHT_MODE			EXTERNAL

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if DEBUG_BUILD == ENABLE

#define DEBUG_PRINT(x) Serial.print(x)			// if DEBUG_BUILD is not enabled thease will be removed automaticy but will not cause an error
#define DEBUG_PRINTLN(x) Serial.println(x)		// if DEBUG_BUILD is not enabled thease will be removed automaticy but will not cause an error
#define TP(message) Serial.println(message);	// if DEBUG_BUILD is not enabled any TP in the code will cause an error, use for testing code that you intend to remove

#else

#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)

#endif

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 10				// maximum number of recordable errors

#define C_MIN_LINE_POINTS 10			// minimum number of points in a line
#define C_MAX_LIDAR_BUFFER 10			// maximum number of buffers lidar packets befor they are discarded

#define LA_MOUNT_OFFSET		60.0		// angle of the LIDAR when mounted to the drone
#define LA_SAFTEY_RADIUS	2000.0		// the maximum radius used to consider objects for colision avoidance
#define LA_MIN_RADIUS		500.0		// the radius of the drone (used to ognor the feet of the drone)

#define C_CORRELATION_SIZE	10
#define C_THRESHOLD			0.95
#define C_MIN_SIZE			10

// DO NOT CHANGE ANYTHING BELOW HERE

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ COMPONENTS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if ENABLE_INDICATOR == ENABLE
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
	#define THROTTLE_COMS
#endif
#if COM_MODE == SERIAL
	#define COM_SERIAL		Serial
	#define C_COM_SEND_RATE 1
#define THROTTLE_COMS
#endif

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

// default thread priorities
#define INDICATOR_PRI	1
#define COM_PRI			5
#define GYRO_PRI		0		// The position system cant run if this is enabeld, to much pacekt loss causing an overflow
#define FLIGHT_PRI		1
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

#define C_APM_ROLL_IN		4
#define C_APM_PITCH_IN		5
#define C_APM_THROTTLE_IN	6
#define C_APM_YAW_IN		7

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
#define MB_OUTBOUND_COUTN		11		// must match the numebr of packets!!
#define MB_OUTBOUND_OFFSET		11		// must match the lowest ID

#define MB_ROLL_PITCH_YAW		11
#define MB_STATUS				12
#define MB_LAST_LIDAR			13
#define MB_COMPENSATOR_VECTOR	14
#define MB_JOY_VECTOR			15
#define MB_TOTAL_VECTOR			16
#define MB_SCHEDULAR_MONITOR	17
#define MB_ANCHOR_1				18
#define MB_ANCHOR_2				19
#define MB_ANCHOR_3				20
#define MB_ANCHOR_4				21


