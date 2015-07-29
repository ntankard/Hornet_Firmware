#pragma once

// Select one

//#define MEGA
#define APM_26

#ifdef APM_26

#define C_COMMS_XBEE Serial2
#define C_COMMS_MAX_RETRY 4
#define C_COMMS_BAUD_RATE 9600
#define C_COMMS_BSTATION_ADDRESS 0x0000

#define C_ACC_CS ACC_CS



#endif