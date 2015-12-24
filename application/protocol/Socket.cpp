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

#define DBG(x) std::cout << x << std::endl;
#include <iostream>

Socket::Socket() {}

Socket::Socket( int msgsock ) : sockfd( msgsock )
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




SocketIp4::SocketIp4( const Ipv4 & ip ) : ip(ip)
{
        sockfd = socket ( AF_INET, SOCK_STREAM, 0 );

        saddr.sin_family = AF_INET;

        saddr.sin_addr.s_addr = ip.getAddressNum();

        saddr.sin_port = htons( PORT );
}

SocketIp4::SocketIp4( int msgsock ) : Socket( msgsock )
{
}

int SocketIp4::bind()
{
        int reuseaddr = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

        int ret = ::bind( sockfd, (struct sockaddr *) &saddr, sizeof( saddr ) ); 

        if(ret != 0)
                throw BindSockEx();

        return ret;
}

int SocketIp4::connect()
{
        DBG("con()")

        int ret = ::connect( sockfd, (struct sockaddr *) &saddr, sizeof( saddr ) );

        if( ret != 0 )
                throw ConnectSockEx();

        return ret;
}

int SocketIp4::accept()
{
        DBG("acc()")
        socklen_t addrlen = sizeof( saddr );

        int msgsock = ::accept( sockfd, (struct sockaddr *) &saddr, &addrlen  );

        if( msgsock == -1 )
                throw AcceptSockEx();

        return msgsock;
}

int SocketIp4::recv( char * buffer, int bufferSize )
{
        DBG("rec()")
        return ::read( sockfd, buffer, bufferSize );
}

int SocketIp4::send( char * buffer, int bufferSize )
{
        DBG("send()")
        return ::send( sockfd, buffer, bufferSize, 0 );
}


Ipv4 SocketIp4::getIp()
{
        return Ipv4( inet_ntoa( saddr.sin_addr ) );
}
