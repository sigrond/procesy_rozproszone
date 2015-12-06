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
        std::string address;
        
        /**
         * \brief     Metoda sprawdzająca poprawność otrzymanego adresu
         * \param[in] Adres IP w postaci ciągu znaków
         * \return    Czy jest poprawny
         */
        virtual bool isCorrect ( const std::string & address ) = 0 const;
};


/**
 * \bref Klasa opakowująca IPv4
 */
class Ipv4 : public Ip
{
public:
        Ipv4 ( const std::string & address = "127.0.0.1" );

private:
        bool isCorrect ( const std::string & address ) const;
};

/*
 * \brief Klasa opakowująca IPv6
 */
class Ipv6 : public Ip
{
public:
        Ipv6 ( const std::string & address = "::1" );

private:
        bool isCorrect ( const td::string & address ) const;
};


/*
 * \brief Wyjątek sygnalizujący błędny adres IP
 */
class badIpException : public std::exception
{
public:
       const char* what();
};

#endif // IP_HPP
