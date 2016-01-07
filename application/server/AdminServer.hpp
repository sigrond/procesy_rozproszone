/** \file AdminServer.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy serwera administratora
 * \date
 * Low Orbit Task Cannon
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "../protocol/ConnectionManager.hpp"
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
    AdminServer(Ip &ip,unsigned short adminPort=55000);
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
    /** \brief Metoda odpowiada za wewnętrzne życie AdminServer'a.
     * Należy raczej oczekiwać, że będzie się zawieszała na funkcjach
     * blokujących, więc powinna być raczej uruchamiana w osobnym wątku.
     * \return void
     */
    void start();
    void triggerShutDown();
    /**
     *-1 - stan początkowy nie ustawione nasłuchiwanie
     * 0 - nasłuchiwanie na rozpoczęcie
     * 1 - odebraliśmy komunikat i wysyłamy ACK
     * 2 - wysłaliśmy ACK i wysyłamy OK lub ERR
     * 3 - odbieramy ACK i znów nasłychujemy
     */
    int state;
private:
    BlockingQueue<Event*>* blockingQueue;
    ConnectionManager* connectionManager;
    Ip* adminIP;/**< opcjonalne IP admina */
    bool shutDown;/**< przełącznik do kończenia pracy AdminServer'a */
    unsigned short port;/**< port konsoli administratora na który wysyłamy */
};
