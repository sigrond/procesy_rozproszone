/*
 * \file     Connection.hpp
 *
 * \brief    Plik nagłówkowy klasy odpowiadającej za połączenie z hostem w warstwie aplikcji
 * 
 * \version  0.1
 * \date     06.12.2015
 *
 * \author   Andrzej Roguski
 *
 * \todo     Deklaracje metod i pól prywatnych
 * \todo     Wyjątki
 */

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <mutex>

#include "Ip.hpp"
#include "Message.hpp"
#include "Socket.hpp"

/**
 * \brief  Klasa realizująca połączenie LOTC
 * 
 *         Każdy obiekt klasy Connection jest związany z jednym hostem (a dokładniej - jego adresem IP)
 *         i odpowiada za całość komunikacji pomiędzy maszyną lokalną a zdalnym hostem w trakcie
 *         całego czasu życia połączenia LOTC.
 *
 * \date   06.12.2015
 *
 * \author Andrzej Roguski
 */
class Connection
{
public:
        /**
         * \brief      Konstruktor połączeń po IPv4
         * \param[in]  address Referencja do obiektu zawierającego adres IPv4 hosta docelowego (domyślnie - localhost) 
         */
        Connection ( const Ipv4 & address = Ipv4(), unsigned short port = 55555, unsigned short clientPort = 0 );

        /**
         * \brief      Konstruktor połączeń po IPv6
         * \param[in]  address Referencja do obiektu zawierającego adres IPv6 hosta docelowego (domyślnie - localhost) 
         */
        Connection ( const Ipv6 & address = Ipv6() );
       
        Connection ( int socket );

        /**
         * \brief      Destruktor
         */
        ~Connection ();

        /**
         * \brief      Funcja wysyłająca komunikat
         * \param[in]  message Referencja do obiektu zawierającego komunikat do wysłania
         */
        void send ( const message::Message & message );

        /**
         * \brief      Funkcja oczekująca na komunikat od zdalnego hosta
         * \return     Wskaźnik na obiekt Message utworzony na podstawie danych otrzymanych ze zdalnego hosta 
         */
        void receive ( message::Message *& message );
private:
        Ip * ip;

        Socket * socket;

	void recDep ( message::Message * & message );
	void recTask ( message::Message * & message, char code );
	void recFile ( message::Message * & message );
	void recErr ( message::Message * & message, char code );
	void recHost ( message::Message * & message, char code );
	void recRet ( message::Message * & message );
};
#endif // CONNECTION_HPP
