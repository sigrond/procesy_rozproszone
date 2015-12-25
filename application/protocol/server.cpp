// banalny serwer
// przyjmuje trzy "komunikaty"

#include "ConnectionManager.hpp"

#include <string>
using namespace message;

int main( int argc, char** argv)
{
        ConnectionManager * mietek = ConnectionManager::getInstance();
        Message * msg1 = nullptr;

        Message * msg2 = new pingMessage( State::REQ );

        getchar();

        mietek->receive( Ipv4(std::string(argv[1]) ), msg1 );

        mietek->send( Ipv4(std::string(argv[1]) ), *msg2 );

        return 0;
}
