/**
 * Low Orbit Task Cannon
 *
 * \file   Address.hpp
 *
 * \brief  Plik nagłówkowy klasy Address
 *
 * \author Andrzej Roguski
 *
 * \date   04.01.2016
 */

#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "Ip.hpp"

/**
 * \brief Klasa bazowa przechowująca parę port, IP
 */
class Address
{
public:
	/**
	 * \brief           Konstruktor
	 *
	 * \param[in] port  numer portu
	 */
	Address( unsigned short port );
	
	/**
	 * \brief  Zwraca numer portu
	 *
	 * \return numer port 
	 */
	unsigned short getPort() const;

protected:
	unsigned short port;
};

/**
 * \brief Klasa przechowująca parę port, IPv4
 */
class AddressIpv4 : public Address
{
public:
	/**
	 * \brief           Konstruktor
	 *
	 * \param[in] ip    adres IPv4
	 *
	 * \param[in] port  numer portu
	 */
	AddressIpv4( Ipv4 ip, unsigned short port );

	/**
	 * \brief Zwraca przechowywany obiekt Ipv4
	 *
	 * \return przechowywany obiekt Ipv4
	 */
	Ipv4 getIp() const;

	/**
	 * \brief           Operator <
	 *                  Służy wyłącznie do znajdywania elementów w kontenerach uporządkowanych,
	 *                  nie tworzy żadnego "sensownego" porządku.
	 * \param[in] that  porównywany obiekt
	 *
	 * \return          czy mniejszy
	 */
	bool operator<( const AddressIpv4 & that ) const;

	/**
	 * \brief           Operator =
	 *
	 * \param[in] that  przypisywany obiekt
	 *
	 * \return          obiekt po przypisaniu
	 */
	AddressIpv4& operator=( const AddressIpv4 & that ); 

private:
	Ipv4 ip;
};


class AddressIpv6 : public Address
{
public:
	AddressIpv6( Ipv6 ip, unsigned short port );

	Ipv6 getIp() const;

private:
	const Ipv6 ip;
};

#endif // ADDRESS_HPP
