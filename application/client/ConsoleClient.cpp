/** \file ConsoleClient.cpp
 * \authors Tomasz Jakubczyk, Kacper Stachyra
 * \brief Implementacje metod klasy ConsoleClient
 *
 */


#include "ConsoleClient.hpp"


//maksymalna liczna polecenia + argumentow
#define ARGS 3

using namespace std;
using namespace message;

ConsoleClient::ConsoleClient()
{
    connected = 0;
    requestAnswered = 1;
    connectionManager=ConnectionManager::getInstance(50000);
}

void ConsoleClient::start()
{
    string arg[ARGS];

    while(true)
    {
        int command = readCommand(arg);

        if (command == EXT)
        {
            cout<<"Wylaczam konsole administratora\n";
            break;
        }
        if (command == CON)
        {
            try
            {
                Ipv4 serverip = Ipv4(arg[1]);
                //connected = connect(serverip);
                pingMessage* m1=new pingMessage(message::State::REQ);
                Message* m2=nullptr;
                connectionManager->send(serverip,*m1);
				connectionManager->receive(serverip,m2);
				connected=true;
                if (connected == 1) cout<<"Pomyslnie polaczono z serwerem";
            }
            catch(BadIpException)
            {
                cout<<"Podaj poprawny adres ip serwera\n";
            }
        }
        else if (command == ADD)
        {
            if (connected)
            {
                //przygotowanie do wyslania wiadomosci do serwera
            }
            else
            {
                cout<<"Brak polaczenia z serwerem\n";
            }
        }


        //...//
        sendCommand();
        checkAnswer();
    }
}

int ConsoleClient::readCommand(string* arg)
{
    //komenda poczatkowo jako nieznana
    command_t command = NC;

    //wczytywanie linii
    string s;
    getline(cin, s);

    stringstream ss;
    ss<<s;

    //zerowanie arg[]
    for (int i=0; i<ARGS; ++i)
    {
        arg[i].clear();
    }

    //czytanie argumentow arg[] z wprowadzonej linii
    for (int i=0; i<ARGS; ++i)
    {
        s.clear();
        ss>>s;

        if(s.length()==0)
            break;

        arg[i]=s;
    }

    //sprawdzanie wprowadzonej komendy
    if (arg[0].compare("exit")==0) command = EXT;
    else if (arg[0].compare("connect")==0) command = CON;

    return command;
}

bool ConsoleClient::connect(Ipv4* ip)
{

}


void ConsoleClient::sendCommand()
{

}

void ConsoleClient::checkAnswer()
{

}
