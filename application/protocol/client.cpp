// Banalny klient testowy
// sprawdza działanie zamykania i otwierania nowych połączeń

#include "ConnectionManager.hpp"

#include <string>


using namespace message;

int main( int argc, char** argv)
{
        ConnectionManager * mietek = ConnectionManager::getInstance();
        
        Message * msg1 = nullptr;

        Message * msg2 = new pingMessage( State::REQ );

        getchar();

        mietek->send( Ipv4(std::string(argv[1])) , *msg2 );
        
        mietek->receive( Ipv4(std::string(argv[1])), msg1 );

        return 0;
}
