// hardware libreys (do not remove)
#include <Servo.h>
#include <RPLidar.h>


// local components
#include "HornetManager.h"
#include "ComsDecoder.h"
#include "Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
#include "Monitor.h"
#include "Indicator.h"
#include "Scheduler.h"
#include "Lidar.h"
#include "Drone.h"

#include "CONFIG.h"

// core componenets
HornetManager *manager;
Error *error;

// coms systems
Coms *coms;
ComsDecoder *comsDecoder;
ComsEncoder *comsEncoder;

// periferal systerms
AccGyro *accGyro;
Monitor *monitor;
Indicator *indicator;
Lidar *lidar;
Drone *drone;

Scheduler *scheduler;

Servo _frontLeft;
Servo _frontRight;
Servo _backLeft;
Servo _backRight;


void setup()
{
	Serial.begin(9600);				//@TODO remove
	error = new Error();
	manager = new HornetManager(error);

	// construct the coms
	comsDecoder = new ComsDecoder(manager);
	coms = new Coms(comsDecoder);

	comsEncoder = new ComsEncoder(coms, error);
	manager->attachComs(coms);
	manager->attachComsEncoder(comsEncoder);

	// construct thew accselerator and gyro
	accGyro = new AccGyro(manager);
	manager->attachAccGyro(accGyro);

	// construct the monitor
	monitor = new Monitor(comsEncoder);
	manager->attachMonitor(monitor);

	// construct the indicator
	indicator = new Indicator();
	manager->attachIndicator(indicator);

	// construct the lidar
	lidar = new Lidar(manager);
	manager->attachLidar(lidar);

	drone= new Drone();
	manager->attachDrone(drone);

	// construct the scedulor
	scheduler = new Scheduler(coms, comsEncoder, accGyro, indicator, lidar);
	manager->attachScheduler(scheduler);

	// start all objest with threads
	manager->start();
}

void loop()
{
	if (manager->run())
	{

	}
	else
	{
		delete manager;
		delete error;
		delete coms;
		delete comsDecoder;
		delete comsEncoder;
		delete accGyro;
		delete monitor;
		delete indicator;
		delete scheduler;

		setup();
	}


}



/*



Coms com(Serial2);
Indicator in;

String toHex2(uint8_t b)
{
	String hex[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
	uint8_t hi;
	uint8_t lo;
	hi = (b >> 4);
	lo = (b & 0b00001111);
	return hex[hi] + hex[lo];
}

uint8_t payload[] = { 1, 2 };

void setup()
{
	//Serial2.begin(9600);
   add setup code here 
	//Serial.begin(9600);
Serial.begin(9600);
 Serial.print("hello");
	delay(1000);
	//com.send(payload, sizeof(payload));
	in.setOn(in.BLUE, true);
	in.setOn(in.RED, true);
	in.setOn(in.YELLOW, true);

	in.setBlinks(in.RED, 2);
	in.setBlinks(in.YELLOW, 1);

	in.setBlinkRate(in.YELLOW, 100);
	in.setBlinkRate(in.RED, 200);
}


void loop()
{
in.run();
delay(10);
*/
	//com.run();
	/*if (Serial3.available())
	{
		Serial.println(toHex2(Serial3.read()));
	}*/

	/*uint8_t payload[] = { 'h','e','l'};
	if (com.canSend())
	{
		//com.send(payload, sizeof(payload));
		payload[0] = payload[0]++;
    delay(1000);
	}*/
	
  /* add main program code here */

