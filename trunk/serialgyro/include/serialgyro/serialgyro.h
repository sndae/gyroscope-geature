#ifndef SP_
#define SP_

#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>


class SerialPort
{
public:

         SerialPort();


         SerialPort(char *port, int baudRate);


        ~SerialPort();


        int readData(char *readBuffer, int bytesToRead);

        bool readChar(char &data);

        int writeData(char *writeBuffer, int bytesToWrite);

        bool openPort();


        void closePort();


        void setRate(int baudRate);

        void setPort(char *port);

        bool isOpen();

protected:

        bool portIsOpen;


        int fileDescriptor;


        char *portName;


        int portBaudRate;


        int configurePort(int fd, int baudRate);
};
#endif
