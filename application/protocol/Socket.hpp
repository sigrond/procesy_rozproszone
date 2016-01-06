/*
 * \file     Socket.hpp
 *
 * \brief    Obiektowy wrapper dla API socketów
 *
 * \author   Andrzej Roguski
 *
 */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Ip.hpp"
#include "SocketException.hpp"

const unsigned short BACKLOG = 256;

const unsigned short TIMEOUT = 10;

class Socket
{
public:
        Socket( unsigned short port );

        Socket( int msgsock, unsigned short port );

        virtual ~Socket();

        virtual int connect();
        
	virtual int connect( unsigned short clientPort );

        virtual int bind();
        int listen();
        virtual int accept();

        virtual int recv( char * buffer, int bufferSize );
        virtual int send( char * buffer, int bufferSize );

        virtual Ipv4 getIp();

	virtual unsigned short getPort() const;

        int close();

protected:
        int sockfd;

	unsigned short port;
};

class SocketIp4 : public Socket
{
public:
        SocketIp4( const Ipv4 & ip, unsigned short port, bool accSock = false );

        SocketIp4( int msgsock );

        virtual int bind();

        virtual int connect();

	virtual int connect( unsigned short clientPort );

	virtual int accept();

        virtual int recv( char * buffer, int bufferSize );

        virtual int send( char * buffer, int bufferSize );

        virtual Ipv4 getIp();

	virtual unsigned short getPort() const;

private:
        sockaddr_in saddr;

        Ipv4 ip;
};

class SocketIp6 : public Socket
{
public:
        SocketIp6( const Ipv6 & ip);

private:
        sockaddr_in6 saddr;
        sockaddr_in6 caddr;
};




#endif // SOCKET_HPP
