#pragma once
#include "APM_2_5_PINS.h"


//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define BOARD_TYPE_APM 1
#define BOARD_TYPE_MEGA 2

// Pick wich board to use
#define BOARD_TYPE BOARD_TYPE_APM

#if BOARD_TYPE == BOARD_TYPE_APM
	#define USE_ACC
#endif

#if BOARD_TYPE == BOARD_TYPE_MEGA

#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- COMM SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------



#define COM_MODE_SERIAL 1
#define COM_MODE_XBEE 2

// pick wich com system to use
#define COM_MODE COM_MODE_SERIAL

#if COM_MODE == COM_MODE_XBEE
	#define C_COMS_PORT Serial2
	#define C_COMS_BAUD_RATE 9600
	#define C_COMMS_BSTATION_ADDRESS 0x0000
#endif 

#if COM_MODE == COM_MODE_SERIAL
#define C_COMS_PORT Serial
	#define C_COMS_BAUD_RATE 9600
	#define C_COMS_BUFFER 100
#endif

#define C_COMS_CODE_CONNECT_REQUEST 'a'
#define C_COMS_CODE_CONNECT_CONFIRM 'b'


//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- ERROR SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 100

#define E_ILLEGAL_ACCESS 1


//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- LOGGER SETTINGS --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_LOGGER_ACC_RATE 10


// pick wich componets are conected and active
//#if BOARD_TYPE == APM
//#define USE_ACC	//built in
//#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ SETTINGS ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


#define C_CONNECT_PULSE_TIME 1000

// Select one

//#define MEGA
//#define APM_26

// Select one
//#define USE_XBEE
//#define USE_SERIAL


/*
#define C_COMS_SERIAL Serial

#ifdef APM_26

#define C_COMMS_XBEE Serial2
#define C_COMMS_MAX_RETRY 4
#define C_COMMS_BAUD_RATE 9600
#define C_COMMS_BSTATION_ADDRESS 0x0000





#endif

*/

#define C_ACC_CS ACC_CS