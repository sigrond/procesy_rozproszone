// Banalny klient testowy
// sprawdza działanie zamykania i otwierania nowych połączeń

#include "Connection.hpp"


int main()
{
        Connection connection = Connection( Ipv4() );

        connection.send( message::synMessage( message::State::REQ ) );
        connection.send( message::synMessage( message::State::REQ ) );
        connection.send( message::synMessage( message::State::REQ ) );

        return 0;
}
