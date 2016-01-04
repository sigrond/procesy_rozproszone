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
#include "MessageCodes.hpp"
// chwilowo
#include <cstring>
#include <iostream>

#include "debug.h"

#include "pasta.h"

// papa, 128 mega ramu
const unsigned long BUF_SIZE = 128 * 1024 * 1024;

Connection::Connection ( const Ipv4 & address, unsigned short port ) : counter(0)
{
        DBG("Connection( " << address.getAddress() <<" )")       
        socket = new SocketIp4( address, port );

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
	
	if( socket )
		delete socket;
}

void Connection::send ( const message::Message & message )
{
        DBG("Conn::send()")

        if( counter < 4 )
        {
                // int i = roll(); 

                // socket->send( pasta[i], sizeof( pasta[i] ) / sizeof( char ) );
		
		
		
		socket->send( message.getBuffer(), message.getBufferSize() );
        }

        if( ++counter > 3 )
                socket->close();
}

void Connection::receive ( message::Message * message )
{
        DBG("Conn::rec()")
        
        if( counter < 4 )
        {
		// jestem pewien, że da się sprytniej
		char * buffer = new char [ BUF_SIZE ];

		memset( buffer, 0, sizeof( buffer ) );

		unsigned long received = socket->recv( buffer, sizeof( buffer ) / sizeof ( char ) );

		switch( (message::Category)( buffer[0] & 0xE0 ) )
		{
			case message::Category::HOST:
				break;
			case message::Category::TASK:
				break;
			case message::Category::DEP:
				break;
			case message::Category::FILE:
				break;
			case message::Category::RET:
				break;
			case message::Category::SYN:
				message = new message::synMessage( buffer, received );
				break;
			case message::Category::PING:
				break;
			case message::Category::ERR:
				break;
		};

		delete buffer;

                //char delicious_pasta[2000];

                //memset( delicious_pasta, 0, sizeof( delicious_pasta ));
              
                //socket->recv( delicious_pasta, sizeof( delicious_pasta ) / sizeof( char ) );
                //std::string pastaStr( delicious_pasta );

                //std::cout << "Received delicious pasta:" << std::endl << std::endl << pastaStr << std::endl << std::endl;
        }

        if( ++counter > 3 )
                socket->close();
}

char Connection::getCounter()
{        
        return counter;
}
