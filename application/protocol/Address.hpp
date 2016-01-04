/** 
 * \file   Address.hpp
 *
 * \brief  Plik nagłówkowy klasy Address
 *
 * \author Andrzej Roguski
 */

#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "Ip.hpp"

class Address
{
public:
	Address( unsigned short port );

	unsigned short getPort() const;

protected:
	unsigned short port;
};

class AddressIpv4 : public Address
{
public:
	AddressIpv4( Ipv4 ip, unsigned short port );

	Ipv4 getIp() const;

	bool operator<( const AddressIpv4 & that ) const;

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
