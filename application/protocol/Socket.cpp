/*
 * \file     Socket.cpp
 * 
 * \author   Andrzej Roguski
 *
 * \todo     WYJĄTKI!!!
 */


// >2015
// >sprawdzanie zwracanej wartości w celu wyłapania błędów


#include "Socket.hpp"
#include <string>
#include <cstring>

#include "debug.h"

Socket::Socket( unsigned short port ) : port(port)
{
}

Socket::Socket( int msgsock, unsigned short port ) : sockfd( msgsock ), port(port)
{
}

Socket::~Socket() {}
int Socket::bind() {}
int Socket::connect() {}
int Socket::accept() {}
int Socket::send( char*, int ) {}
int Socket::recv( char*, int ) {}
Ipv4 Socket::getIp() {}

int Socket::listen()
{
        DBG("Socket::listen()")

        int ret = ::listen( sockfd, BACKLOG );

        if( ret != 0 )
                throw ListenSockEx();

        return ret;
}

int Socket::close()
{
        shutdown( sockfd, 2 );
        return ::close( sockfd );
}




SocketIp4::SocketIp4( const Ipv4 & ip, unsigned short port ) : Socket( port ), ip(ip)
{
        DBG("SocketIp4( " << ip.getAddress() << " )")

        sockfd = socket ( AF_INET, SOCK_STREAM, 0 );

        saddr.sin_family = AF_INET;

        saddr.sin_addr.s_addr = ip.getAddressNum();

        saddr.sin_port = htons( port );
}

SocketIp4::SocketIp4( int msgsock ) : Socket( msgsock, 0 )
{
        DBG("SocketIp4( " << msgsock << " )")
}

int SocketIp4::bind()
{
        DBG("SocketIp4::bind()")

        int reuseaddr = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

        int ret = ::bind( sockfd, (struct sockaddr *) &saddr, sizeof( saddr ) ); 

        if(ret != 0)
                throw BindSockEx();

        return ret;
}

int SocketIp4::connect()
{
        DBG("SocketIp4::connect()")

        int ret = ::connect( sockfd, (struct sockaddr *) &saddr, sizeof( saddr ) );

        if( ret != 0 )
                throw ConnectSockEx();

        return ret;
}

int SocketIp4::accept()
{
        DBG("SocketIp4::accept()")

        socklen_t addrlen = sizeof( saddr );

        int msgsock = ::accept( sockfd, (struct sockaddr *) &saddr, &addrlen  );

        if( msgsock == -1 )
                throw AcceptSockEx();

        return msgsock;
}

int SocketIp4::recv( char * buffer, int bufferSize )
{
        DBG("SocketIp4::recv()")

        int bytesRec;
	unsigned bytesTotal = 0;

        while( bufferSize > 0 )
        {
                bytesRec = ::read(sockfd, buffer, bufferSize);
                
                if (bytesRec == 0)
                        break;

                else if (bytesRec < 0)
                        break;

                buffer += bytesRec;
                bufferSize -= bytesRec;
		bytesTotal += bytesRec;
        }

        return bytesTotal; 
}

int SocketIp4::send( char * buffer, int bufferSize )
{
        DBG("SocketIp4::send()")

        int bytesSent;

        while( bufferSize > 0 )
        {
                bytesSent = ::send(sockfd, buffer, bufferSize, 0);
                
                if (bytesSent == 0)
                        break;

                else if (bytesSent < 0)
                        break;

                buffer += bytesSent;
                bufferSize -= bytesSent;
        }

        return bytesSent; 
}


Ipv4 SocketIp4::getIp()
{
        return Ipv4( inet_ntoa( saddr.sin_addr ) );
}
