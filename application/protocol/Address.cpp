/** 
 * \file   Address.cpp
 *
 * \brief  Plik z defunicją klasy Address
 *
 * \author Andrzej Roguski
 */

#include "Address.hpp"

Address::Address( unsigned short port ) : port(port)
{
}

unsigned short Address::getPort() const
{
	return port;
}


AddressIpv4::AddressIpv4( Ipv4 ip, unsigned short port ) : Address(port), ip(ip)
{

}

Ipv4 AddressIpv4::getIp() const
{
	return ip;
}

bool AddressIpv4::operator<( const AddressIpv4 & that ) const
{
	if( ip < that.getIp() || ( ip == that.getIp() && port < that.getPort() ) )
		return true;

	else
		return false;
}

AddressIpv4 & AddressIpv4::operator=( const AddressIpv4 & that )
{
	ip = that.ip;
	port = that.port;
	return *this;
}


AddressIpv6::AddressIpv6( Ipv6 ip, unsigned short port ) : Address(port), ip(ip)
{

}

Ipv6 AddressIpv6::getIp() const
{
	return ip;
}


