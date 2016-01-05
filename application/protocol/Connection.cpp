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

void Connection::recTask ( message::Message * & message, char code )
{
	char * buffer = new char [ 11 ];
	memset( buffer, 0, sizeof( buffer ) );
	socket->recv( buffer, 11 );

	bool rPriority = true;

	if( (unsigned char)buffer[0] == 0x00 )
		rPriority = false;

	unsigned short priority = 0;

	priority += (unsigned)buffer[1];
	priority += (unsigned)buffer[2] << 8;
	
	unsigned long taskId = 0;

	taskId += (unsigned long)buffer[3];
	taskId += (unsigned long)buffer[4] << 8;
	taskId += (unsigned long)buffer[5] << 16;
	taskId += (unsigned long)buffer[6] << 24;

	unsigned long l = 0;

	l += (unsigned long)buffer[3];
	l += (unsigned long)buffer[4] << 8;
	l += (unsigned long)buffer[5] << 16;
	l += (unsigned long)buffer[6] << 24;

	std::chrono::steady_clock::duration d (l);

	std::chrono::steady_clock::time_point t(d);

	unsigned char sub = (unsigned char)code & 0x1C;

	message = new message::taskMessage( (message::TaskSub)sub, message::State::REQ, rPriority, priority, taskId, t );
}
void Connection::recFile ( message::Message * & message )
{

}
void Connection::recErr ( message::Message * & message )
{

}
void Connection::recHost ( message::Message * & message )
{

}
void Connection::recRet ( message::Message * & message )
{

}

void Connection::recDep ( message::Message * & message )
{
	char * buf = new char [ 3 ];
	memset( buf, 0, sizeof( buf ) );
	socket->recv( buf, 3 );

	unsigned tasksSize = 0;

	tasksSize += (unsigned)buf[1];
	tasksSize += (unsigned)buf[2] << 8;

	delete [] buf;

	char * buffer = new char [tasksSize * 4];
	memset( buffer, 0, sizeof(buffer) );
	socket->recv( buffer, tasksSize * 4 );
	
	std::vector<unsigned long> tasks (tasksSize, 0);

	for( unsigned i = 0; i < tasksSize; ++i )
	{
		tasks[i] += (unsigned long)buffer[ i * 4     ];
		tasks[i] += (unsigned long)buffer[ i * 4 + 1 ] << 8;
		tasks[i] += (unsigned long)buffer[ i * 4 + 2 ] << 16;
		tasks[i] += (unsigned long)buffer[ i * 4 + 3 ] << 24;
	}

	message = new message::depMessage( message::State::REQ, tasks );

	delete [] buffer;

}

void Connection::receive ( message::Message * & message )
{
        DBG("Conn::rec()")
        
        if( counter < 4 )
        {
		char * code = new char [ 1 ];

		memset( code, 0, sizeof( code ) );

		unsigned long received = socket->recv( code, 1 );

		switch( (message::Category)( (unsigned)code[0] & 0xE0 ) )
		{
			case message::Category::HOST:
				if( (unsigned)code[0] & 0x03 == 0x00 )
				{
					recHost( message );	
				}
				else
					message = new message::hostMessage( (message::State)( (unsigned)code[0] & 0x03 ) );

				break;

			case message::Category::TASK:
				if( (unsigned)code[0] & 0x03 == 0x00 )
				{
					recTask( message, code[0] );
				}
				else
					message = new message::taskMessage( (message::State)( (unsigned)code[0] & 0x03 ) );

				break;

			case message::Category::DEP:
				if( ((unsigned)code[0] & 0x03) == 0x00 )
					recDep( message );
				else
					message = new message::depMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
				break;

			case message::Category::FILE:
				if( (unsigned)code[0] & 0x03 == 0x00 )
				{
					recFile( message );
				}
				else
					message = new message::fileMessage( (message::State)( (unsigned)code[0] & 0x03 ) );

				break;

			case message::Category::RET:
				if( (unsigned)code[0] & 0x03 == 0x00 )
				{
					recRet( message );
				}
				else
					message = new message::depMessage( (message::State)( (unsigned)code[0] & 0x03 ) );

				break;

			case message::Category::SYN:
				message = new message::synMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
				break;

			case message::Category::PING:
				message = new message::pingMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
				break;

			case message::Category::ERR:
				if( (unsigned)code[0] & 0x03 == 0x00 )
				{
					recErr( message );
				}
				else
					message = new message::depMessage( code, received );

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
