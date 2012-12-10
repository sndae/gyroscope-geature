#include <boost/asio.hpp>

class serialBoost
{
private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
public:
    serialBoost(std::string port, unsigned int baudrate);
    std::string readBoost();
    void writeBoost(std::string s);
};
