/** \file AdminServer.h
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy serwera administratora
 *
 */

#pragma once

/** \brief klasa serwera administratora
 */
class AdminServer
{
public:
    AdminServer();
    void listen();/**< metoda nasłuchująca na połączenie z konsoli administratora */
    void connect();/**< metoda łącząca się z konsolą administratora */
};
