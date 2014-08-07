#ifndef POLOLU_MAESTRO
#define POLOLU_MAESTRO

/**************************************
 * pololuMaestroMotorController.h
 * Matthew Bailey
 * 2014-03-25
 *
 * This file describes an interface
 * to the Pololu Maestro 
 * servo controller on the Ducted Fan 
 * Hovercraft that controls the four
 * servos, the main fan, and the height
 * sensor.
 *
 ***************************************/

#include <string>
#include "serialDevice.h"

class PololuMaestroMotorController {
  public:
    static const int DEFAULT_BAUD = 115200;
  	PololuMaestroMotorController(int deviceID = 12, std::string _port = std::string("/dev/ttyACM1"));
  	~PololuMaestroMotorController();

    int reset();
  	int sendCommand(int channel, char* command, int length);
    int setTarget(int channel, int target);
  	int getData(int channel, int& data); //char* dataBuffer);
    int goHome();
    int getErrors(unsigned int& errors);

  private:
  	SerialDevice* ser;
  	int id;
    std::string port;
};

#endif
