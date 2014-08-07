#ifndef FAN_H
#define FAN_H

/**************************************
 * fan.h
 * Matthew Bailey
 * NEEC: Navy Robot Project
 * 2014-03-25
 *
 * This file describes an interface
 * to the main fan of the 
 * Ducted Fan Hovercraft.
 * This code uses the pololu maestro
 * motor controller interface.
 *
 ***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "pololuMaestroMotorController.h"
//#include "fan.h"

class FanController {
public:
	FanController(PololuMaestroMotorController* m);
	~FanController();
	double getSpeed();
	double setSpeed(double speed, int dev = 0);
private:
	FanController();
	PololuMaestroMotorController* mc;
};
//#include "gpio-event-drv.h"

FanController::FanController() {}

FanController::FanController(PololuMaestroMotorController* m) {
	mc = m;
}

FanController::~FanController() {
}

double FanController::setSpeed(double speed, int dev) {
	int target = (int)(4*speed);
   	mc->setTarget(dev, target);
	return speed;
}

#endif
