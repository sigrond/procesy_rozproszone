/**
 * \file Ip.cpp
 *
 * \brief Plik z implementacjami metod klasy Ip
 *
 * \authors Tomasz Jakubczyk, Andrzej Roguski
 *
 * \todo IPv6
 *
 */

#include <regex>

#include "Ip.hpp"

#include <iostream>

// ------------------------------------------------------
// Ip
// ------------------------------------------------------
Ip::Ip(){}
Ip::~Ip(){}


// ------------------------------------------------------
// Ipv4
// ------------------------------------------------------
Ipv4::Ipv4 ( const std::string & str ) : addrStr(str)
{
        if( ! isCorrect( str ) )
                throw BadIpException();

        inet_aton( str.c_str(), &address );
}

Ipv4::Ipv4 ( const Ipv4 & that )
{
	addrStr = that.getAddress();
	inet_aton( addrStr.c_str(), &address);
}

bool Ipv4::isCorrect ( const std::string & str ) const
{
        // ten koszmar poniżej to regex sprawdzający, czy ciąg jest poprwanym adresem IPv4 w konwencji A.B.C.D
        const static std::regex exIpv4("(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
	
        return std::regex_match( str, exIpv4 );
}


std::string Ipv4::getAddress() const
{
        return addrStr;
}

unsigned long Ipv4::getAddressNum() const
{
        return address.s_addr;
}

bool Ipv4::operator<( const Ipv4 & that ) const
{
       return getAddressNum() < that.getAddressNum();
}


bool Ipv4::operator==( const Ipv4 & that ) const
{
        return getAddressNum() == that.getAddressNum();
}

Ipv4 & Ipv4::operator=( const Ipv4 & that )
{
	addrStr = that.getAddress();
	inet_aton( addrStr.c_str(), &address);
	return *this;
}

// ------------------------------------------------------
// Ipv6
// ------------------------------------------------------
Ipv6::Ipv6 ( const std::string & str )
{

}

bool Ipv6::isCorrect () const
{
	return true;
}

void Ipv6::toNumbers()
{

}

std::string Ipv6::getAddress() const
{
        return "";
}


// ------------------------------------------------------
// BadIpException
// ------------------------------------------------------

const char* BadIpException::what()
{
	return "badIpException";
}
