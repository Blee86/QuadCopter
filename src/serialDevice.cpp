#ifndef SERIAL_DEVICE
#define SERIAL_DEVICE

/**************************************
 * serialDevice.h
 * Matthew Bailey
 * NEEC: Navy Robot Project
 * 2014-03-25
 *
 * This file describes an interface
 * to a serial device.
 *
 ***************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <string>
//#include "serialDevice.h"


class SerialDevice {
  public:
static const int DEFAULT_BAUD = 115200;
static const int BUFFERSIZE   = 2;
  	SerialDevice(char* newPort, int newBaud = SerialDevice::DEFAULT_BAUD);
    	SerialDevice(std::string newPort, int newBaud = SerialDevice::DEFAULT_BAUD);
  	~SerialDevice();
  	int readByte(char*);
  	int writeByte(char*);
  	int readBytes(char*, int);
  	int writeBytes(char*, int);

  private:
  	SerialDevice();
    void alternateSetup(std::string, int);
  	int fd;
  	char* buffer;
  	int baud;
//  	char* port;
    std::string port;
  	struct termios ttyAttr;
};

SerialDevice::SerialDevice() { }
SerialDevice::SerialDevice(char* newPort, int newBaud) {
  port = std::string(newPort);
	baud = newBaud;
	buffer = new char[BUFFERSIZE];

	fd = open(port.c_str(), O_RDWR | O_NONBLOCK);
  if(fd < 0)
    std::cout << "FAILED TO INITIALIZE SERIAL DEVICE " << port << std::endl;
	tcgetattr (fd, &ttyAttr);
	cfsetospeed (&ttyAttr, (speed_t)B115200);
//	cfsetispeed (&ttyAttr, (speed_t)B115200);
  cfsetispeed (&ttyAttr, (speed_t)B9600);
	tcsetattr(fd, TCSANOW, &ttyAttr); 
}

SerialDevice::SerialDevice(std::string newPort, int newBaud) {
  alternateSetup(newPort, newBaud);

/*  port = newPort;
  baud = newBaud;
  buffer = new char[BUFFERSIZE];

  fd = open(port.c_str(), O_RDWR); //  | O_NONBLOCK);
  if(fd < 0)
    std::cout << "FAILED TO INITIALIZE SERIAL DEVICE " << port << std::endl;
  tcgetattr (fd, &ttyAttr);
  cfsetospeed (&ttyAttr, (speed_t)B115200);
//  cfsetispeed (&ttyAttr, (speed_t)B115200);
  cfsetispeed(&ttyAttr, (speed_t)B9600);
  tcsetattr(fd, TCSANOW, &ttyAttr); 
*/}

void SerialDevice::alternateSetup(std::string newPort, int newBaud) {
  int USB = open( newPort.c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY );
  struct termios tty;
  struct termios tty_old;
  memset (&tty, 0, sizeof tty);

  /* Error Handling */
  if ( tcgetattr ( USB, &tty ) != 0 )
  {
  std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
  }

  /* Save old tty parameters */
  tty_old = tty;

  /* Set Baud Rate */
  cfsetospeed (&tty, (speed_t)B115200); // B9600);
  cfsetispeed (&tty, (speed_t)B115200); //B9600);

  /* Setting other Port Stuff */
  tty.c_cflag     &=  ~PARENB;        // Make 8n1
  tty.c_cflag     &=  ~CSTOPB;
  tty.c_cflag     &=  ~CSIZE;
  tty.c_cflag     |=  CS8;

  tty.c_cflag     &=  ~CRTSCTS;       // no flow control
  tty.c_cc[VMIN]      =   1;                  // read doesn't block
  tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout
  tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

  /* Make raw */
  cfmakeraw(&tty);

  /* Flush Port, then applies attributes */
  tcflush( USB, TCIFLUSH );
  if ( tcsetattr ( USB, TCSANOW, &tty ) != 0)
  {
  std::cout << "Error " << errno << " from tcsetattr" << std::endl;
  }
  fd = USB;
}

SerialDevice::~SerialDevice() {
	delete [] buffer;
	buffer = NULL;
	close(fd);
}

int SerialDevice::readByte(char* buff) {
	return readBytes(buff, 1);
}

int SerialDevice::writeByte(char* buff) {
	return writeBytes(buff, 1);
}

int SerialDevice::readBytes(char* buff, int numBytes) {
	return read(fd, buff, numBytes);
}

int SerialDevice::writeBytes(char* buff, int numBytes) {
	return write(fd, buff, numBytes);
}

#endif
