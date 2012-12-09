#include <ros/ros.h>
#include <serialgyro/serialgyro.h>
#include <iostream>

int main(int argv, char ** argc)
{
    ros::init(argv,argc,"serialtest");
    std::string portname = "/dev/ttyACM0";
    SerialPort serial((char *)portname.c_str(),9600);
    if(!serial.openPort())
    {
        std::cout<<"Serial port is not opened properly"<<std::endl;
        abort();
    }
    std::string data ="madhukar";
    serial.writeData((char *)data.c_str(),5);
    return 0;
}
