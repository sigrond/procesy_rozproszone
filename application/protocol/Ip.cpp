/** \file Ip.cpp
 *
 * \authors Tomasz Jakubczyk, ...
 * \brief Plik z implementacjami metod klasy Ip
 * \todo Andrzej napisze
 *
 */

#include "Ip.hpp"

Ip::Ip ( const std::string & address ) : address(address)
{

}

Ip::~Ip()
{

}

const std::string & Ip::getAddress () const
{
	return address;
}

Ipv4::Ipv4 ( const std::string & address ) : Ip(address)
{

}

bool Ipv4::isCorrect ( const std::string & address ) const
{
	return true;
}

Ipv6::Ipv6 ( const std::string & address ) : Ip(address)
{

}

bool Ipv6::isCorrect ( const std::string & address ) const
{
	return true;
}

const char* badIpException::what()
{
	return "badIpException";
}














