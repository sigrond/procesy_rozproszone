#include "ConsoleClient.hpp"

using namespace std;

ConsoleClient::ConsoleClient()
{
    connected = 0;
    requestAnswered = 1;

}

void ConsoleClient::start()
{
    /*while (!connected)
    {
        connected = connect();
    }*/

    int command = readCommand();

}

bool ConsoleClient::connect()
{

}

int ConsoleClient::readCommand()
{
    string arg[3];
    command_t command;

    //czytanie wprowadzonej linii do argumentow w arg[]
    string s;
    while (getline(cin, s))
    {
        stringstream ss;
        ss<<s;

        for (int i=0; i<3; ++i)
        {
            s.clear();
            ss>>s;

            cout<<s;
            if(s.length()==0)
                break;

        }
    }
    return 0;
}

void ConsoleClient::sendCommand()
{

}

void ConsoleClient::checkAnswer()
{

}
