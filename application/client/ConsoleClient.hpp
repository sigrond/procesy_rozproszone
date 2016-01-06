/** \file ConsoleClient.hpp
 * \authors Tomasz Jakubczyk, Kacper Stachyra
 * \brief plik nagłówkowy klasy ConsoleClient
 *
 */

#ifndef ConsoleClient_hpp
#define ConsoleClient_hpp

#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <set>

#include "../protocol/ConnectionManager.hpp"
#include "../server/BlockingQueue.hpp"

using namespace std;

class ConsoleClient
{
public:
    ConsoleClient();

    /*czy klient polaczony do serwera*/
    bool connected;

    /*funkcja inicjujaca polaczenie i prace klienta*/
    void start();

    /*typ wyliczeniowy dla czytanych z konsoli polecen*/
    enum command_t
    {
        NC, /*nierozpoznana komenda*/
        CON, /*polacz*/
        ADD, /*nowe zadanie*/
        EXT, /*wyjscie*/
    };

private:
    /*czy otrzymano odpowiedz od serwera*/
    bool requestAnswered;

    /*czyta komendy wpisywane do konsoli*/
    int readCommand(string* arg);

    /*ustanawia polaczenie z serwerem*/
    bool connect(Ipv4* ip);
    //bool connect();

    /*wysyla polecenie do serwera i czeka na odpowiedz*/
    void sendCommand();

    /*sprawdza poprawnosc odpowiedzi od serwera*/
    void checkAnswer();

    ConnectionManager* connectionManager;

    BlockingQueue<message::Message*> q;

    void listenAndRecognize();

    void sendFromQueue();

    bool shutDown;

    bool anyResponse;
    bool pingAck;
    bool fileAck;
    bool taskAck;
    Ipv4 serverip;
    int taskCount;
};

#endif

