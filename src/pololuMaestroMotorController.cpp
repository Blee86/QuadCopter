#ifndef POLOLU_MAESTRO
#define POLOLU_MAESTRO

/**************************************
 * pololuMaestroMotorController.h
 * Matthew Bailey
 * NEEC: Navy Robot Project
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
//#include "PololuMaestroMotorController"

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

PololuMaestroMotorController::PololuMaestroMotorController(int deviceID, std::string _port) {
  id = deviceID;
  port = _port;
  ser = new SerialDevice(_port);
}

PololuMaestroMotorController::~PololuMaestroMotorController() {
  delete ser;
  ser = NULL;
}

int PololuMaestroMotorController::reset() {
  char command[3];
  command[0] = 0xaa;
  command[1] = 0x0c;
  command[2] = 0x22;

  ser->writeBytes(command, 3);

  return 0;
}

int PololuMaestroMotorController::sendCommand(int channel, char* command, int length) {
  ser->writeBytes(command, length);
  return 0;
}

int PololuMaestroMotorController::setTarget(int channel, int target) {
  // setup command
  char command[6];
  command[0] = 0xaa;
  command[1] = 0x0c;
  command[2] = 0x04;
  command[3] = char(channel);
  command[4] = char(target & 0x7f);
  command[5] = char((target >> 7) & 0x7f);

  int returnVal = 0;
  returnVal |= ser->writeBytes(command, 6);
  return returnVal;
}

int PololuMaestroMotorController::getData(int channel, int& value) { //char* dataBuffer) {
  // setup command
  char command[4];
  command[0] = 0xaa;
  command[1] = 0x0c;
  command[2] = 0x10;
  command[3] = char(channel);

  // setup data buffer
//  delete [] dataBuffer;
//  dataBuffer = new char[3];
  char dataBuffer[3];
  int returnVal = 0;

  returnVal |= ser->writeBytes(command, 4);   // Ask polulo for info
  returnVal |= ser->readBytes(dataBuffer, 2); // read 2 byte response

  value = (((int)dataBuffer[0] & 0xff) | (((int)dataBuffer[1] & 0xff) << 8));
  return returnVal;
}

int PololuMaestroMotorController::goHome() {
  // setup command
  char command[6];
  command[0] = 0xaa;
  command[1] = 0x0c;
  command[2] = 0x22;

  int returnVal = 0;
  returnVal |= ser->writeBytes(command, 3);
  return returnVal;
}

int PololuMaestroMotorController::getErrors(unsigned int& errors) {
/*
  0: Serial Signal Error (bit 0)
    A hardware-level error that occurs when a byte’s stop bit is not detected 
    at the expected place. This can occur if you are communicating at a baud 
    rate that differs from the Maestro’s baud rate.
  1: Serial Overrun Error (bit 1)
    A hardware-level error that occurs when the UART’s internal buffer fills up. 
    This should not occur during normal operation.
  2: Serial RX buffer full (bit 2)
    A firmware-level error that occurs when the firmware’s buffer for bytes 
    received on the RX line is full and a byte from RX has been lost as a result. 
    This error should not occur during normal operation.
  3: Serial CRC error (bit 3)
    This error occurs when the Maestro is running in CRC-enabled mode and the 
    cyclic redundancy check (CRC) byte at the end of the command packet does not 
    match what the Maestro has computed as that packet’s CRC (Section 5.d). 
    In such a case, the Maestro ignores the command packet and generates a CRC error.
  4: Serial protocol error (bit 4)
    This error occurs when the Maestro receives an incorrectly formatted or nonsensical 
    command packet. For example, if the command byte does not match a known command or 
    an unfinished command packet is interrupted by another command packet, this error occurs.
  5: Serial timeout error (bit 5)
    When the serial timeout is enabled, this error occurs whenever the timeout period has 
    elapsed without the Maestro receiving any valid serial commands. This timeout error can 
    be used to make the servos return to their home positions in the event that serial 
    communication between the Maestro and its controller is disrupted.
  6: Script stack error (bit 6)
    This error occurs when a bug in the user script has caused the stack to overflow or 
    underflow. Any script command that modifies the stack has the potential to cause this 
    error. The stack depth is 32 on the Micro Maestro and 126 on the Mini Maestros.
  7: Script call stack error (bit 7)
    This error occurs when a bug in the user script has caused the call stack to overflow 
    or underflow. An overflow can occur if there are too many levels of nested subroutines, 
    or a subroutine calls itself too many times. The call stack depth is 10 on the Micro Maestro 
    and 126 on the Mini Maestros. An underflow can occur when there is a return without a 
    corresponding subroutine call. An underflow will occur if you run a subroutine using the 
    “Restart Script at Subroutine” serial command and the subroutine terminates with a return 
    command rather than a quit command or an infinite loop.
  8: Script program counter error (bit 8)
    This error occurs when a bug in the user script has caused the program counter 
    (the address of the next instruction to be executed) to go out of bounds. 
    This can happen if your program is not terminated by a quit, return, or infinite loop.
*/

  // setup command
  char command[6];
  command[0] = 0xaa;
  command[1] = 0x0c;
  command[2] = 0x21;

  char dataBuffer[3];
  int returnVal = 0;

  returnVal |= ser->writeBytes(command, 3);
  returnVal |= ser->readBytes(dataBuffer, 2); // read 2 byte response

  errors = (((int)dataBuffer[0] & 0xff) | (((int)dataBuffer[1] & 0xff) << 8));
  return returnVal;
}

#endif
