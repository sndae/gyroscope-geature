#include <ros/ros.h>
#include <boost/asio.hpp>
#include <serialboost/serialboost.h>

using namespace std;
using namespace boost;

int main(int argv,char ** argc)
{
    ros::init(argv,argc,"serialtest");
    try
    {
        std::string portname = "/dev/ttyACM0";
        serialBoost serial(portname,9600);
        serial.writeBoost("Hello world\n");
        cout<<serial.readBoost()<<endl;
    }catch(boost::system::system_error &e)
    {
        cout<<"Error : "<<e.what()<<endl;
    }
}
