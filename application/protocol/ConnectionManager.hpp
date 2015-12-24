/* 
 * \file     ConnectionManager.hpp
 *
 * \brief    Plik nagłówkowy klasy zarządzajacej polączeniami
 *
 * \author   Andrzej Roguski
 *
 */

#ifndef CONNECTON_MANAGER_HPP
#define CONNECTION_HPP

#include "Message.hpp"
#include "Ip.hpp"

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
        ConnectionManager & getInstance();

        /*
         * \brief           Wysyła komunikat msg do hosta o adresie ip
         * \param[in]  ip   Adres na który ma być wyslana wiadomość
         * \param[in]  msg  Wiadomość do wysłania
         */
        void send( const Ip & ip, const message::Message & msg );

        /* 
         * \brief           Czeka na wiadomość od hosta o adresie ip
         * \param[in]  ip   Adres z którego ma przyjść wiadomość
         * \param[out] msg  Wskaźnik do oczekiwanej wiadomości
         */ 
        void receive( const Ip & ip, message::Message * const msg );

private:
        ConnectionManager();
        ConnectionManager( const ConnectionManager & );
        ConnectionManager& operator=( const ConnectionManager & );
        ~ConnectionManager();

        std::map<Ipv4, Connection> Map4;
};

#endif // CONNECTON_MANAGER_HPP
