/* 
 * \file     ConnectionManager.hpp
 *
 * \brief    Plik nagłówkowy klasy zarządzajacej polączeniami
 *
 * \author   Andrzej Roguski
 *
 */

#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <map>


#include "Message.hpp"
#include "Ip.hpp"
#include "Connection.hpp"
#include "Socket.hpp"

/*
 * \brief Singleton zarządzający połączeniami
 */
class ConnectionManager
{

public:
        /*
         * \brief   Zwraca referencję do obiektu ConnectionManager. Jesli taki nie istnieje, tworzy go.
         * \return  Referencja do obiektu ConnectionManager
         */
        static ConnectionManager * getInstance();

        /*
         * \brief           Wysyła komunikat msg do hosta o wskazanym adresie IPv4
         * \param[in]  ip   Adres na który ma być wyslana wiadomość
         * \param[in]  msg  Wiadomość do wysłania
         */
        void send( const Ipv4 & ip, const message::Message & msg );

        /*
         * \brief           Wysyła komunikat msg do hosta o wskazanym adresie IPv6
         * \param[in]  ip   Adres na który ma być wyslana wiadomość
         * \param[in]  msg  Wiadomość do wysłania
         */
        void send( const Ipv6 & ip, const message::Message & msg );
        
        /* 
         * \brief           Czeka na wiadomość od hosta o wskazanym adresie IPv4
         * \param[in]  ip   Adres z którego ma przyjść wiadomość
         * \param[out] msg  Wskaźnik do oczekiwanej wiadomości
         */ 
        void receive( const Ipv4 & ip, message::Message * const msg );

        /* 
         * \brief           Czeka na wiadomość od hosta o wskazanym adresie IPv6
         * \param[in]  ip   Adres z którego ma przyjść wiadomość
         * \param[out] msg  Wskaźnik do oczekiwanej wiadomości
         */ 
        void receive( const Ipv6 & ip, message::Message * const msg );
        
        /*
         * \brief           Usuwa IPv4 z mapy.
         * \param[in]  ip   Adres IP do usunięcia
         */
        void remove( const Ipv4 & ip );

        /*
         * \brief           Usuwa IPv6 z mapy.
         * \param[in]  ip   Adres IP do usunięcia
         */
        void remove( const Ipv6 & ip );
        
        typedef std::map<Ipv4, Connection*>::iterator iterator4;
        typedef std::map<Ipv6, Connection*>::iterator iterator6;
private:
        ConnectionManager();
        ConnectionManager( const ConnectionManager & );
        ConnectionManager& operator=( const ConnectionManager & );
        ~ConnectionManager();

        std::map<Ipv4, Connection*> map4;

        Socket * listeningSocket;

        friend void awaitConnections( ConnectionManager * conMan );

        // Soon™
        // std::map<Ipv6, Connection*> map6;
};

#endif // CONNECTION_MANAGER_HPP
