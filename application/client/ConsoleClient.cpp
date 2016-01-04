#include "ConsoleClient.hpp"

using namespace std;

ConsoleClient::ConsoleClient()
{
    connected = 0;
    requestAnswered = 1;

}

void ConsoleClient::start()
{
    while (!connected)
    {
        connected = connect();
    }

    int command = readCommand();

}

bool ConsoleClient::connect()
{

}

int ConsoleClient::readCommand()
{
    string s;
    while (getline(cin, s))
    {
        if(s.compare("exit")==0)
        {
            cout<<"Wylaczam konsole administratora...\n";
            break;
        }
        else
        {
            stringstream ss;
            ss<<s;
            while(1)
            {
                s.clear();
                ss>>s;

                if (s.compare("connect"))
                {
                    command = 1;
                }

                cout<<s;
                if(s.length()==0)
                    break;
            }
        }
    }
    return
}

void ConsoleClient::sendCommand()
{

}

void ConsoleClient::checkAnswer()
{

}
