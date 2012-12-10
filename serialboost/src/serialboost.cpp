#include <serialboost/serialboost.h>


serialBoost::serialBoost(std::string port, unsigned int baudrate):io(),serial(io,port)
{
    serial.set_option(boost::asio::serial_port_base::baud_rate(baudrate));
}

void serialBoost::writeBoost(std::string s)
{
    boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
}

std::string serialBoost::readBoost()
{
    char c;
    std::string result;
    using namespace boost;
    for(;;)
    {
        asio::read(serial,asio::buffer(&c,1));
        switch(c)
        {
            case '\n':
                return result;
            default:
                result+=c;
        }
    }
}
