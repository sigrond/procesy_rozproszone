#include "ConsoleClient.hpp"

//maksymalna liczna polecen argumentow
#define ARGS 3

using namespace std;

ConsoleClient::ConsoleClient()
{
    connected = 0;
    requestAnswered = 1;
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
                connected = connect(serverip);
            }
            catch(BadIpException)
            {
                cout<<"Podaj poprawny adres ip serwera\n";
            }
        }
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
