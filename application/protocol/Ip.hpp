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
#include <array>
#include <netinet/in.h>
#include <arpa/inet.h>

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
        Ip ();
        virtual ~Ip ();
        
        /**
         * \brief  Metoda zwracająca przechowywany adres IP jako ciąg znaków
         * \return Adres IP
         */
        virtual std::string getAddress () const = 0;
};



/**
 * \bref Klasa opakowująca IPv4
 */
class Ipv4 final : public Ip
{
public:
        /**
         * \brief Konstruktor.
         *
         * \param[in] address referencja do stringu z adresem IPv4 w konwencji A.B.C.D 
         */
        Ipv4 ( const std::string & address = "127.0.0.1" );

        /**
         * \brief  Zwraca adres IPv4 w konwencji A.B.C.D
         *
         * \return string z adresem
         */
        virtual std::string getAddress () const;

        /**
         * \brief  Zwraca adres IPv4 w postaci przechowywanej przez strukturę in_addr.
         *
         * \return liczba z adresem w postaci bitowej
         */
        unsigned long getAddressNum () const;

        /**
         * \brief     Operator < (mniejszy niż). 
         *
         * Służy włącznie do wprowadzenia **jakiegokolwiek** porządku w zbiorze adresów.
         * Nie musi to być koniecznie porządek typu 10.10.10.10 < 10.10.10.11.
         * Rzeczywiste uporządkowanie zależy ot tego, co inet_aton() wyprawia z adresami.
         *
         * \param[in] porównywany obiekt
         *
         * \return    czy porównywany obiekt jest "mniejszy"
         */
        bool operator<( const Ipv4 & that ) const;

private:
        bool isCorrect ( const std::string & str ) const;

        in_addr address;
};




/*
 * \brief Klasa opakowująca IPv6
 */
class Ipv6 final : public Ip
{
public:
        Ipv6 ( const std::string & address = "::1" );

        virtual std::string getAddress () const;
private:
        bool isCorrect () const;
        void toNumbers();
        
       unsigned long addressNumbers[4];
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
