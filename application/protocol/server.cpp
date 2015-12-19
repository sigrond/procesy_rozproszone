// banalny serwer
// przyjmuje trzy "komunikaty"

#include "Connection.hpp"

int main()
{
        Connection connection = Connection( Ipv4() );
        connection.receive( );
        connection.receive( );
        connection.receive( );

        return 0;
}
