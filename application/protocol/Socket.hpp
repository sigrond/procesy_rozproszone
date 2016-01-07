/**
 * Low Orbit Task Cannon
 *
 * \file     Socket.hpp
 *
 * \brief    Plik nagłówkowy klas Socket
 *
 * \author   Andrzej Roguski
 *
 * \date     19.12.2015
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

/**
 * \brief Klasa bazowa Socket - obiektowy wrapper dla API socketów
 */
class Socket
{
public:
	/**
	 * \brief Konstruktor
	 *
	 * \param[in] port serwera 
	 */
	Socket( unsigned short port );

	/**
	 * \brief Konstruktor
	 *
	 * \param[in] msgsock deskryptor socketu
	 *
	 * \parem[in] port    port serwera
	 */
	Socket( int msgsock, unsigned short port );

	/**
	 * \brief Destruktor
	 */
	virtual ~Socket();

	virtual int connect();

	virtual int connect( unsigned short clientPort );

	virtual int bind();

	/**
	 * \brief Ustawia socket w tryb nasluchiwania
	 */
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
	/**
	 * \brief           Konstruktor - tworzy nowy socket
	 *
	 * \param[in] ip    adres IP zdalnego hosta
	 *
	 * \param[in] port  port zdalnego hosta
	 */
	SocketIp4( const Ipv4 & ip, unsigned short port );

	/**
	 * \brief              Konstruktor - używa istniejącego socketu
	 *
	 * \param[in] msgsock  deskryptor socketu
	 *
	 */
	SocketIp4( int msgsock );

	/**
	 * \brief Wiąże socket z adresem
	 */
	virtual int bind();

	/**
	 * \brief Łączy z serwerem
	 */
	virtual int connect();

	/**
	 * \brief                 Łączy ze zdalnym hostem za pomoca ustalonego portu
	 *
	 * \param[in] clientPort  numer portu wyjściowego używanego do łączenia ze zdalnym hostem
	 */
	virtual int connect( unsigned short clientPort );

	/**
	 * \brief Przyjmuje połączenia
	 */
	virtual int accept();

	/**
	 * \brief                     Odbiera dane i zapisuje do bufora
	 *
	 * \param[in|out] buffer      wskazanie na bufor
	 *
	 * \param[in]     bufferSize  rozmiar bufora
	 */
	virtual int recv( char * buffer, int bufferSize );

	/**
	 * \brief                     Wysyła dane z bufora
	 *
	 * \param[in|out] buffer      wskazanie na bufor
	 *
	 * \param[in]     bufferSize  rozmiar bufora
	 */
	virtual int send( char * buffer, int bufferSize );

	/**
	 * \brief Zwraca adres IPv4 zdalengo hosta
	 */
	virtual Ipv4 getIp();

	/**
	 * \brief Zwraca port zdalnego hosta
	 */
	virtual unsigned short getPort() const;

private:
	sockaddr_in saddr;

	Ipv4 ip;
};

class SocketIp6 : public Socket
{
public:
	SocketIp6( const Ipv6 & ip);

	SocketIp6( int msgsock );

	virtual int bind();

	virtual int connect();

	virtual int connect( unsigned short clientPort );

	virtual int accept();

	virtual int recv( char * buffer, int bufferSize );

	virtual int send( char * buffer, int bufferSize );


private:
	sockaddr_in6 saddr;
	sockaddr_in6 caddr;
};

#endif // SOCKET_HPP
