#ifndef ConsoleClient_hpp
#define ConsoleClient_hpp

#include <iostream>
#include <string>
#include <sstream>

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
        EXIT, /*wyjscie*/
    };

private:
    /*czy otrzymano odpowiedz od serwera*/
    bool requestAnswered;

    /*czyta komendy wpisywane do konsoli*/
    int readCommand(string* arg);

    /*ustanawia polaczenie z serwerem*/
    bool connect();

    /*wysyla polecenie do serwera i czeka na odpowiedz*/
    void sendCommand();

    /*sprawdza poprawnosc odpowiedzi od serwera*/
    void checkAnswer();
};

#endif

