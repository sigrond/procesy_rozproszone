/** 
 * \file Connection.cpp
 *
 * \brief Plik z implementacjami metod klasy Connection.
 *
 * \authors Tomasz Jakubczyk, Andrzej Roguski
 */

#include <fstream>
#include <boost/crc.hpp>

#include "Connection.hpp"
#include "MessageCodes.hpp"

#include <cstring>
#include <iostream>

#include "debug.h"

Connection::Connection ( const Ipv4 & address, unsigned short port, unsigned short clientPort )
{
        DBG("Connection( " << address.getAddress() << ":" << port <<" )")       
        socket = new SocketIp4( address, port );

	if( port != 55555 )
		socket->connect();
	else
		socket->connect( clientPort );
}

Connection::Connection ( const Ipv6 & address )
{

}

Connection::Connection ( int msgsock )
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

	socket->send( message.getBuffer(), message.getBufferSize() );

	socket->close();
}

void Connection::recTask ( message::Message * & message, char code )
{
	DBG_M("Conn::recTask() TASK REQ");
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

	l += (unsigned long)buffer[7];
	l += (unsigned long)buffer[8] << 8;
	l += (unsigned long)buffer[9] << 16;
	l += (unsigned long)buffer[10] << 24;

	std::chrono::steady_clock::duration d (l);

	std::chrono::steady_clock::time_point t(d);

	unsigned char sub = (unsigned char)code & 0x1C;

	message = new message::taskMessage( (message::TaskSub)sub, message::State::REQ, rPriority, priority, taskId, t );
}

void Connection::recFile ( message::Message * & message )
{
	DBG_M("Conn::recFile() FILE REQ");
	char * buffer = new char [11];
	memset( buffer, 0, sizeof( buffer ) );
	socket->recv( buffer, 11 );

	unsigned char fnameSize = buffer[0] & 0x8F;

	bool isMainF = false;

	if( ( buffer[0] & 0x80 ) == 0x00 )
		isMainF = true;

	unsigned short checksum = 0;
	checksum  = (unsigned char)buffer[1];
	checksum += (unsigned char)buffer[2] << 8;

	unsigned long taskId = 0;
	taskId += (unsigned long)buffer[3];
	taskId += (unsigned long)buffer[4] << 8;
	taskId += (unsigned long)buffer[5] << 16;
	taskId += (unsigned long)buffer[6] << 24;

	unsigned long filesize = 0;
	filesize += (unsigned long)buffer[7];
	filesize += (unsigned long)buffer[8] << 8;
	filesize += (unsigned long)buffer[9] << 16;
	filesize += (unsigned long)buffer[10] << 24;

	delete [] buffer;

	char * fbuf = new char [ filesize + fnameSize ];
	memset( fbuf, 0, sizeof( fbuf ) );
	socket->recv( fbuf, filesize + fnameSize );

	std::string filename;

	for(unsigned short i = 0; i < fnameSize; ++i )
		filename.push_back( fbuf[i] );
	
	unsigned long fileStart = fnameSize;

	boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false>  crc;

	for(unsigned long i = 0; i < filesize; ++i )
		crc.process_byte( fbuf[ fileStart + i ] );

	if( checksum != crc() )
		throw "CRC Fail."; // TODO klasa wyjątku

	std::ofstream out ( filename );
	
	for(unsigned long i = 0; i < filesize; ++i )
		out << fbuf[ fileStart + i ]; 

	out.close();

	delete [] fbuf;

	message = new message::fileMessage( message::State::REQ, isMainF, taskId, filename );
}

void Connection::recErr ( message::Message * & message, char code )
{
	DBG_M("Conn::recErr() ERR REQ");
	char * buffer = new char [1];
	memset( buffer, 0, sizeof( buffer ) );
	socket->recv( buffer, 1 );

	unsigned char errCode = (unsigned char)buffer[1];

	unsigned char sub = (unsigned char)code & 0x1C;

	message = new message::errMessage( (message::ErrSub)sub, message::State::REQ, errCode );

}
void Connection::recHost ( message::Message * & message, char code )
{
	DBG_M("Conn::recHost() HOST REQ");
	char * buf = new char [ 3 ];
	memset( buf, 0, sizeof( buf ) );
	socket->recv( buf, 3 );
	
	bool ipv6 = true;

	if( (unsigned char)buf[0] == 0x00 )
		ipv6 = false;

	unsigned addrSize = 0;

	addrSize += (unsigned)buf[1];
	addrSize += (unsigned)buf[2] << 8;

	delete [] buf;

	if( ipv6 )
	{
		;
	}
	else
	{
		char * buffer = new char [ addrSize * 4];

		memset( buffer, 0, sizeof(buffer) );

		socket->recv( buffer, addrSize * 4 );
		
		std::vector<Ipv4> addr (addrSize);

		in_addr ip;

		for( unsigned i = 0; i < addrSize; ++i )
		{
			ip.s_addr = 0;
			ip.s_addr += (unsigned long)buffer[ i * 4     ];
			ip.s_addr += (unsigned long)buffer[ i * 4 + 1 ] << 8;
			ip.s_addr += (unsigned long)buffer[ i * 4 + 2 ] << 16;
			ip.s_addr += (unsigned long)buffer[ i * 4 + 3 ] << 24;

			addr[i] = Ipv4( inet_ntoa( ip ) );
		}

		unsigned char sub = (unsigned char)code & 0x1C;
		message = new message::hostMessage( (message::HostSub)sub, message::State::REQ, addr );

		delete [] buffer;
	}

}
void Connection::recRet ( message::Message * & message )
{
	DBG_M("Conn::recRet() RET REQ");
	char * buffer = new char [11];
	memset( buffer, 0, sizeof( buffer ) );
	socket->recv( buffer, 11 );

	unsigned char exitStatus = (unsigned char)buffer[0];

	unsigned char fnameSize = (unsigned char)buffer[1];

	unsigned long taskId = 0;
	taskId += (unsigned long)buffer[3];
	taskId += (unsigned long)buffer[4] << 8;
	taskId += (unsigned long)buffer[5] << 16;
	taskId += (unsigned long)buffer[6] << 24;

	unsigned long filesize = 0;
	filesize += (unsigned long)buffer[7];
	filesize += (unsigned long)buffer[8] << 8;
	filesize += (unsigned long)buffer[9] << 16;
	filesize += (unsigned long)buffer[10] << 24;

	delete [] buffer;

	char * fbuf = new char [ filesize + fnameSize ];
	memset( fbuf, 0, sizeof( fbuf ) );
	socket->recv( fbuf, filesize + fnameSize );

	std::string filename;

	for(unsigned short i = 0; i < fnameSize; ++i )
		filename.push_back( fbuf[i] );
	
	unsigned long fileStart = fnameSize;

	std::ofstream out ( filename );
	
	for(unsigned long i = 0; i < filesize; ++i )
		out << fbuf[ fileStart + i ]; 

	out.close();

	delete [] fbuf;

	message = new message::retMessage( message::State::REQ, exitStatus, taskId, filename );

}

void Connection::recDep ( message::Message * & message )
{
	DBG_M("Conn::recDep() DEP REQ");
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
        
	char * code = new char [ 1 ];

	memset( code, 0, sizeof( code ) );

	unsigned long received = socket->recv( code, 1 );

	
	DBG( "Conn::rec() code[0] = " << std::hex << (unsigned)code[0] );
	
	std::cout << std::dec;

	switch( (message::Category)( (unsigned)code[0] & 0xE0 ) )
	{
		case message::Category::HOST:
			if( ((unsigned)code[0] & 0x03) == 0x00 )
			{
				recHost( message, code[0] );	
			}
			else
			{
				DBG_M("Conn::rec() HOST ACK/OK/NOK");
				message = new message::hostMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			}
			break;

		case message::Category::TASK:
			if( ((unsigned)code[0] & 0x03) == 0x00 )
			{
				DBG_M("Conn::rec() TASK ACK/OK/NOK");
				recTask( message, code[0] );
			}
			else
			{
				message = new message::taskMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			}
			break;

		case message::Category::DEP:
			if( ((unsigned)code[0] & 0x03) == 0x00 )
				recDep( message );
			else
			{
				DBG_M("Conn::rec() DEP ACK/OK/NOK");
				message = new message::depMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			}
			break;

		case message::Category::FILE:
			if( ((unsigned)code[0] & 0x03) == 0x00 )
			{
				recFile( message );
			}
			else
			{
				DBG_M("Conn::rec() FILE ACK/OK/NOK");
				message = new message::fileMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			}
			break;

		case message::Category::RET:
			if( ((unsigned)code[0] & 0x03) == 0x00 )
			{
				recRet( message );
			}
			else
			{
				DBG_M("Conn::rec() RET ACK/OK/NOK");
				message = new message::depMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			}
			break;

		case message::Category::SYN:
			DBG_M("Conn::rec() SYN");
			message = new message::synMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			break;

		case message::Category::PING:
			DBG_M("Conn::rec() SYN");
			message = new message::pingMessage( (message::State)( (unsigned)code[0] & 0x03 ) );
			break;

		case message::Category::ERR:
			if( ((unsigned)code[0] & 0x03) == 0x00 )
			{
				recErr( message, code[0] );
			}
			else
			{
				DBG_M("Conn::rec() ERR ACK/OK/NOK");
				message = new message::depMessage( code, received );
			}
			break;

		default:
			DBG("Conn::rec() Nieznana kategoria")
			break;
	};

	delete code;

        
	socket->close();
}
