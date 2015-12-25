/** 
 * \file Connection.cpp
 *
 * \brief Plik z implementacjami metod klasy Connection.
 *
 * \authors Tomasz Jakubczyk, Andrzej Roguski
 */

// UWAGA!!!
// Poniższy kod został wyprodukowany na (bardzo) szybko, w celach uzyskania JAKIEGOKOLWIEK połączenia
// Planowo do wigilii przestanie to wyglądać jak program napisany przez absolwenta szkoły wyższej informatyki i zarządzania



#include "Connection.hpp"

// chwilowo
#include <cstring>
#include <iostream>

#include "debug.h"


#include "pasta.h"

Connection::Connection ( const Ipv4 & address ) : counter(0)
{
        DBG("Connection( " << address.getAddress() <<" )")       
        socket = new SocketIp4( address );

        try
        {
                socket->connect();
        }
        catch (std::exception & e)
        {
                std::cerr << e.what() << std::endl;
        }
}

Connection::Connection ( const Ipv6 & address ) : counter(0)
{

}

Connection::Connection ( int msgsock ) : counter(0)
{
        DBG("Connection( " << msgsock << " )")
        socket = new SocketIp4( msgsock );
}

Connection::~Connection ()
{
        DBG("~Connection(): My ancestors are smiling at me, Imperials. Can you say the same?")
        delete socket;
}

void Connection::send ( const message::Message & message )
{
        DBG("Conn::send()")
        int i = roll(); 

        socket->send( pasta[i], sizeof( pasta[i] ) / sizeof( char ) );

        if( ++counter == 4)
                socket->close();
}

void Connection::receive ( message::Message * const message )
{
        DBG("Conn::rec()")
        char delicious_pasta[2000];

        memset( delicious_pasta, 0, sizeof( delicious_pasta ));
      
        socket->recv( delicious_pasta, sizeof( delicious_pasta ) / sizeof( char ) );
        std::string pastaStr( delicious_pasta );

        std::cout << "Received delicious pasta:" << std::endl << std::endl << pastaStr << std::endl << std::endl;

        if( ++counter == 4)
                socket->close();
}

char Connection::getCounter() const
{
        return counter;
}
