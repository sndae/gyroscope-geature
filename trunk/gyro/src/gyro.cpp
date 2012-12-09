#include <ros/ros.h>
#include <gyro_data/gyro_data.h>
#include <Serialgyro/serialgyro.h>

int main (int argv,char ** argc)
{
    ros::init(argv,argc,"gyro");
    ros::NodeHandle n;
    ros::Publisher gyro_pub = n.advertise<gyro_data::gyro_data>("gyroData",5);
    ros::Rate looprate(10);
    int count = 0;
    std::string portname = "/dev/ttyACM0";
    SerialPort serial((char *)portname.c_str(),9600);
    std::cout<<"in\n";
    if(serial.openPort()==false)
    {
        std::cout<<"Serial Port cannot open\n";
        abort();
    }
    std::cout<<"out\n";
    std::string orientation[3];
    gyro_data::gyro_data msg;
    while(ros::ok())
    {
        int i = 0;
        char  buff;
        do
        {
            buff='1';
            std::cout<<"inside it\n";
            if(serial.readChar(buff))
            {
                std::cout<<buff<<std::endl;
            }
        }while(buff!='\r');
        do
        {
            if(i == 0)
            {
                if(buff==',')
                {
                   i++;
                   continue;
                }
                orientation[i]+=buff;
            }
            else if(i == 1)
            {
                if(buff==',')
                {
                   i++;
                   continue;
                }
                orientation[i]+=buff;
            }
            else
            {
                if(buff == ',')
                {
                   i++;
                   continue;
                }
                orientation[i]+=buff;
            }

        }while(buff !='\n');
        msg.data[0]=atof(orientation[0].c_str())/10;
        msg.data[1]=atof(orientation[1].c_str())/10;
        msg.data[2]=atof(orientation[2].c_str())/10;
        ROS_INFO("Pitch : [%f]",msg.data[0]);
        ROS_INFO("Roll : [%f]",msg.data[1]);
        ROS_INFO("Yaw : [%f]",msg.data[2]);
        gyro_pub.publish(msg);
        ros::spinOnce();
        count++;
        looprate.sleep();
    }
}
