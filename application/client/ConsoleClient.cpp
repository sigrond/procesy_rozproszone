#include "ConsoleClient.hpp"

using namespace std;

ConsoleClient::ConsoleClient()
{
    connected = 0; //czy polaczono z serwerem
    requestAnswered = 1; //czy otrzymano odpowiedz
}

void ConsoleClient::start()
{
    string arg[3];

    while(connected==0)
    {
        int command = readCommand(arg);
        cout<<"komenda przeczytana i jest to "<<command<<"\n";
        cout<<"argumenty: "<<arg[1]<<"   "<<arg[2]<<"\n";
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
    for (int i=0; i<3; ++i)
    {
        arg[i].clear();
    }

    //czytanie argumentow arg[] z wprowadzonej linii
    for (int i=0; i<3; ++i)
    {
        s.clear();
        ss>>s;

        if(s.length()==0)
            break;

        arg[i]=s;
    }

    //sprawdzanie wprowadzonej komendy
    if (arg[0].compare("exit")==0)
    {
        cout<<"exituje";
        command = EXIT;
    }
    else if (arg[0].compare("connect")==0)
    {
        command = CON;
    }

    return command;
}


void ConsoleClient::sendCommand()
{

}

void ConsoleClient::checkAnswer()
{

}
