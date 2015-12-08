#include "ConsoleClient.hpp"

using namespace std;

ConsoleClient::ConsoleClient()
{
    connected = 0;
    requestAnswered = 1;

}

void ConsoleClient::start()
{
    /*tymczasowe*/
    readCommand();
}

int ConsoleClient::connect()
{
    /*polaczenie do serwera i wszystko inne, moze cos zwracac*/
}

void ConsoleClient::readCommand()
{
    /*tymczasowe*/
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
                cout<<s;
                if(s.length()==0)
                    break;
            }
        }
    }
}

void ConsoleClient::sendCommand()
{

}

void ConsoleClient::checkAnswer()
{

}
