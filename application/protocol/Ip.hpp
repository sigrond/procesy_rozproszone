/*
 * \file     Ip.hpp
 *
 * \brief    Plik nagłówkowy klasy opakowującej adresy IP
 * 
 * \version  0.5
 * \date     06.12.2015
 *
 * \author   Andrzej Roguski
 */

#ifndef IP_HPP
#define IP_HPP

#include <string>

/**
 * \brief Abstrakcyjna klasa bazowa dla klas opakuwujących IPv4 i IPv6
 */
class Ip
{
public:
        /**
         * \brief Konstruktor
         * \param address Adres IP
         * \throw badIpException Błędny adres IP
         */
        Ip ( const std::string & address );
       
        virtual ~Ip ();
        
        /**
         * \brief  Metoda zwracająca przechowywany adres IP jako ciąg znaków
         * \return Adres IP
         */
        const std::string & getAddress () const;

protected:
        const std::string address;
};



/**
 * \bref Klasa opakowująca IPv4
 */
class Ipv4 final : public Ip
{
public:
        Ipv4 ( const std::string & address = "127.0.0.1" );

private:
        bool isCorrect () const;
        void splitToNumbers();

        unsigned char addressNumbers [4];
};




/*
 * \brief Klasa opakowująca IPv6
 */
class Ipv6 final : public Ip
{
public:
        Ipv6 ( const std::string & address = "::1" );

private:
        bool isCorrect () const;
        void splitToNumbers();
        unsigned char addressNumbers [16];
};




/*
 * \brief Wyjątek sygnalizujący błędny adres IP
 */
class BadIpException : public std::exception
{
public:
       const char* what();
};

#endif // IP_HPP
