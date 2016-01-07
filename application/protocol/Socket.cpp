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
#include <cerrno>

#include "debug.h"

Socket::Socket( unsigned short port ) : port(port)
{
}

Socket::Socket( int msgsock, unsigned short port ) : sockfd( msgsock ), port(port)
{
	struct timeval tv;

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
}

Socket::~Socket() {}
int Socket::bind() {}
int Socket::connect(){}
int Socket::connect( unsigned short clientPort ) {}
int Socket::accept() {}
int Socket::send( char*, int ) {}
int Socket::recv( char*, int ) {}
Ipv4 Socket::getIp() {}
unsigned short Socket::getPort() const {}

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
	DBG("Socket::Close()" )
        shutdown( sockfd, 2 );

	int c = ::close( sockfd );

	usleep(10000);

        return c;
}



SocketIp4::SocketIp4( const Ipv4 & ip, unsigned short port ) : Socket( port ), ip(ip)
{
        DBG("SocketIp4( " << ip.getAddress() << " )")

        sockfd = socket ( AF_INET, SOCK_STREAM, 0 );

        saddr.sin_family = AF_INET;

        saddr.sin_addr.s_addr = ip.getAddressNum();

        saddr.sin_port = htons( port );

	struct timeval tv;

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	//setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

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

int SocketIp4::connect( unsigned short clientPort )
{
        DBG("SocketIp4::connect( " << clientPort << " )")

	sockaddr_in tmp = saddr;

	saddr.sin_port = htons( clientPort );

	bind();

	saddr = tmp;

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
	/*	if( errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS )
			throw TimeoutEx();
		else*/
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
		DBG("bufSize: " << bufferSize )
                bytesRec = ::read(sockfd, buffer, bufferSize);
                
                if (bytesRec == 0)
                        break;

                else if (bytesRec < 0)
			if( errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS )
				throw TimeoutEx();
			else
				throw RecSockEx();

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
                bytesSent = ::send(sockfd, buffer, bufferSize, MSG_NOSIGNAL);
                
                if (bytesSent == 0)
                        break;

                else if (bytesSent < 0)
                        throw SendSockEx();

                buffer += bytesSent;
                bufferSize -= bytesSent;
        }

        return bytesSent; 
}


Ipv4 SocketIp4::getIp()
{
        return Ipv4( inet_ntoa( saddr.sin_addr ) );
}

unsigned short SocketIp4::getPort() const
{
	return ntohs(saddr.sin_port);
}


