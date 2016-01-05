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

Connection::Connection ( const Ipv4 & address, unsigned short port, unsigned short clientPort ) : counter(0)
{
        DBG("Connection( " << address.getAddress() << ":" << port <<" )")       
        socket = new SocketIp4( address, port );

        try
        {
		if( port != 55555 )
			socket->connect();
		else
			socket->connect( clientPort );
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

void Connection::receive ( message::Message * & message )
{
        DBG("Conn::rec()")
        
        if( counter < 4 )
        {
		char * code = new char [ 1 ];

		memset( code, 0, sizeof( code ) );

		unsigned long received = socket->recv( code, 1 );

		switch( (message::Category)( (int)code[0] & 0xE0 ) )
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
				message = new message::synMessage( code, received );
				break;

			case message::Category::PING:
				message = new message::pingMessage( code, received );
				break;

			case message::Category::ERR:
				break;

			default:
				DBG("Conn::rec() Nieznana kategoria")
				break;
		};

		delete code;
        }

        if( ++counter > 3 )
                socket->close();
}

char Connection::getCounter()
{        
        return counter;
}
