#include "serialgyro/serialgyro.h"
#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>


SerialPort::SerialPort()
{
        portName = NULL;
        portBaudRate = B0;
        portIsOpen = false;
}

SerialPort::SerialPort(char *port, int baudRate)
{
        portName = port; portIsOpen = false;
        portIsOpen = false;
        setRate(baudRate);
}

SerialPort::~SerialPort()
{
        close(fileDescriptor);
}

bool SerialPort::openPort()
{
        if(!portIsOpen && (portName != NULL) )
        {
               fileDescriptor = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
        }
        std::cout<<"inside open port\n"<<std::endl;
        if(fileDescriptor == -1)
        {
               perror("openPort(): Unable to open serial port");
               return false;
        }
        else
        {
               fcntl(fileDescriptor, F_SETFL, 0);
               portIsOpen = true;
               configurePort(fileDescriptor, portBaudRate);
               return true;
        }

}

void SerialPort::setRate(int rate)
  {
      if(!portIsOpen)
      {
          switch (rate)
                {
                   case 38400:
                   default:
                      portBaudRate = B38400;
                      break;
                   case 19200:
                      portBaudRate  = B19200;
                      break;
                   case 9600:
                      portBaudRate  = B9600;
                      break;
                   case 4800:
                      portBaudRate  = B4800;
                      break;
                   case 2400:
                      portBaudRate  = B2400;
                      break;
                   case 1800:
                      portBaudRate  = B1800;
                      break;
                   case 1200:
                      portBaudRate  = B1200;
                      break;
                   case 600:
                      portBaudRate  = B600;
                      break;
                   case 300:
                      portBaudRate  = B300;
                      break;
                   case 200:
                      portBaudRate  = B200;
                      break;
                   case 150:
                      portBaudRate  = B150;
                      break;
                   case 134:
                      portBaudRate  = B134;
                      break;
                   case 110:
                      portBaudRate  = B110;
                      break;
                   case 75:
                      portBaudRate  = B75;
                      break;
                   case 50:
                      portBaudRate  = B50;
                      break;
                }
      }
      else
      {
          ROS_ERROR_STREAM("Serial Port is already been used as name : "<<portName<<
                           ". Hence the rate cannot be changed");
      }
  }

void SerialPort::closePort()
{
        if(portIsOpen)
        {
               close(fileDescriptor);
               portName = NULL;
               fileDescriptor = -1;
        }
}

int SerialPort::readData(char * readBuffer, int bytesToRead)
{
        int bytesRead = -1;

        if(portIsOpen)
        {
               bytesRead = read(fileDescriptor, readBuffer, bytesToRead);
        }
        return bytesRead;
}

bool SerialPort::readChar(char &data)
{
    int bytesRead = 0;
    if(portIsOpen)
    {
        bytesRead = read(fileDescriptor,&data,1);
    }
    return bytesRead;
}

int SerialPort::writeData(char * writeBuffer, int bytesToWrite)
{
        int bytesWritten = -1;

        if(portIsOpen)
        {
                bytesWritten = write(fileDescriptor, writeBuffer, bytesToWrite);
        }

        return bytesWritten;
}

void SerialPort::setPort(char *port)
{
        portName = port;
}

int SerialPort::configurePort(int fd, int baudRate)      // configure the port
{
        struct termios port_settings;      // structure to store the port settings in

        cfsetispeed(&port_settings, baudRate);    // set baud rates
        cfsetospeed(&port_settings, baudRate);
        port_settings.c_cflag |= (CLOCAL | CREAD);
        port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
        port_settings.c_cflag &= ~CSTOPB;
        port_settings.c_cflag &= ~CSIZE;
        port_settings.c_cflag |= CS8;
        port_settings.c_cflag &= ~(ICANON | ECHO | ISIG);
        //port_settings.c_cflag |= (CRTSCTS);
        port_settings.c_cflag |=(IXON | IXOFF | IXANY);
        tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
        return(fd);

}

bool SerialPort::isOpen()
{
        return portIsOpen;
}
