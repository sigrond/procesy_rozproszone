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
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/regex.hpp>

#include "Ip.hpp"


// ------------------------------------------------------
// Ip
// ------------------------------------------------------
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


// ------------------------------------------------------
// Ipv4
// ------------------------------------------------------
Ipv4::Ipv4 ( const std::string & address ) : Ip(address)
{
        if( ! isCorrect() )
                throw BadIpException();

        splitToNumbers();
}

bool Ipv4::isCorrect () const
{
        const static std::regex exIpv4("(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
	
        return std::regex_match( address, exIpv4 );
}

void Ipv4::splitToNumbers()
{
        const static std::regex ex3("[0-9]{1,3}");

        std::smatch matches;
        std::string str = address;

        short i = 0;

        while (std::regex_search ( str, matches, ex3 ) )  
        {
                addressNumbers[i++] = (unsigned char)std::stoi( matches[0] );
                str = matches.suffix().str();
        }
}


// ------------------------------------------------------
// Ipv6
// ------------------------------------------------------
Ipv6::Ipv6 ( const std::string & address ) : Ip(address)
{

}

bool Ipv6::isCorrect () const
{
	return true;
}

void Ipv6::splitToNumbers()
{

}


// ------------------------------------------------------
// BadIpException
// ------------------------------------------------------

const char* BadIpException::what()
{
	return "badIpException";
}














