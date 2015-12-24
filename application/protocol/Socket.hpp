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

// port z dupy wzięty, bardzo możliwe, że tymczasowy
// port nasłuchiwania komunikatów
const unsigned short PORT = 55555; 

const unsigned short BACKLOG = 256;



class Socket
{
public:
        Socket();

        Socket( int msgsock );

        virtual ~Socket();

        virtual int connect();

        virtual int bind();
        int listen();
        virtual int accept();

        virtual int recv( char * buffer, int bufferSize );
        virtual int send( char * buffer, int bufferSize );

        virtual Ipv4 getIp();

        int close();

protected:
        int sockfd;
};

class SocketIp4 : public Socket
{
public:
        SocketIp4( const Ipv4 & ip );

        SocketIp4( int msgsock );

        virtual int bind();

        virtual int connect();

        virtual int accept();

        virtual int recv( char * buffer, int bufferSize );

        virtual int send( char * buffer, int bufferSize );

        virtual Ipv4 getIp();

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
