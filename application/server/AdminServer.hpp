/** \file AdminServer.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy serwera administratora
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "../protocol/Connection.hpp"
/**< \todo potrzebne implementacje Connection */

/** \brief Klasa serwera administratora.
 * Należy się spodziewać raczej asynchronicznego działania.
 */
class AdminServer
{
public:
    /** \brief Konstruktor bez podania adresu administratora.
     * Oznacza to, że czekamy na pierwsze zapytanie z konsoli administratora,
     * a jak już przyjdzie to przyjmujemy jego adres jako adres admina.
     */
    AdminServer();
    /** \brief Konstruktor z podaniem adresu administratora.
     *
     * \param ip Ip& Adres konsoli administratora.
     *
     */
    AdminServer(Ip &ip);
    ~AdminServer();
    /** \brief Metoda nasłuchująca na połączenie z konsoli administratora.
     * Odbiera wiadomość i wrzuca w zdarzeniu do blockingQueue.
     * \return void
     *
     */
    void listen();
    /** \brief Metoda łącząca się z konsolą administratora.
     * Wysyła wiadomość.
     * \param m message::Message* Wiadomość do wysłania.
     * \return void
     *
     */
    void connect(message::Message* m);
    void setBlockingQueue(BlockingQueue<Event*>*);
private:
    BlockingQueue<Event*>* blockingQueue;
    Connection* connection;
    Ip* adminIP;/**< opcjonalne IP admina */
};
