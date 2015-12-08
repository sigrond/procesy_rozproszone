#ifndef ConsoleClient_hpp
#define ConsoleClient_hpp

#include <iostream>
#include <string>
#include <sstream>

#include "ConsoleServer.hpp"

class ConsoleClient
{
public:
    ConsoleClient();

    /*czy klient polaczony do serwera*/
    bool connected;

    /*funkcja inicjujaca polaczenie i prace klienta*/
    void start();

private:
    /*czy otrzymano odpowiedz od serwera*/
    bool requestAnswered;

    /*ustanawia polaczenie z serwerem*/
    int connect();

    /*czyta komendy wpisywane z klawiatury*/
    void readCommand();

    /*wysyla polecenie do serwera i czeka na odpowiedx*/
    void sendCommand();

    /*sprawdza poprawnosc odpowiedzi od serwera*/
    void checkAnswer();
};

#endif

