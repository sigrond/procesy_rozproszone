/** \file ConsoleClient.cpp
 * \authors Tomasz Jakubczyk, Kacper Stachyra
 * \brief Implementacje metod klasy ConsoleClient
 *
 */


#include "ConsoleClient.hpp"
#include <thread>

extern bool demo;


//maksymalna liczna polecenia + argumentow
#define ARGS 3

using namespace std;
using namespace message;

ConsoleClient::ConsoleClient() : shutDown(false)
{
    connected = 0;
    requestAnswered = 1;
    connectionManager=ConnectionManager::getInstance(50000);
    serverip=Ipv4("127.0.0.1");
}

void ConsoleClient::start()
{
    thread listenAndRecognizeThread(&ConsoleClient::listenAndRecognize,this);
    thread sendFromQueueThread(&ConsoleClient::sendFromQueue,this);

    string arg[ARGS];

    int command=NC;

    while(!shutDown)
    {

        if(demo)
        {
        	command=CON;
        	arg[1]="127.0.0.1";
        }
        else
		{
			int command = readCommand(arg);
		}


        if (command == EXT)
        {
            cout<<"Wylaczam konsole administratora\n";
            shutDown=true;
            q.push_back(nullptr);
            break;
        }
        if (command == CON)
        {
        	#ifdef _DEBUG
        	cout<<"command == CON"<<endl;
        	#endif // _DEBUG
            try
            {
                serverip = Ipv4(arg[1]);
            	#ifdef _DEBUG
            	cout<<"próbuję się połączyć z: "<<serverip.getAddress()<<endl;
            	#endif // _DEBUG
                //connected = connect(serverip);
                anyResponse=false;
                pingAck=false;
                pingMessage* m1=new pingMessage(message::State::REQ);
                Message* m2=nullptr;
                pingMessage* m3=new pingMessage(message::State::ACK);
                pingMessage* m4=new pingMessage(message::State::OK);
                //connectionManager->send(serverip,*m1,55555);
                q.push_back(m1);
                #ifdef _DEBUG
                cout<<"ping do serwera LOTC wysłany"<<endl;
                #endif // _DEBUG
				//connectionManager->receive(serverip,m2,55555);
				while(!anyResponse);
				if(pingAck)
				{
					q.push_back(m4);
				}
				//m2->print();
				//connectionManager->receive(serverip,m2,55555);
				//m2->print();
				//connectionManager->send(serverip,*m3,55555);
				connected=true;
                if (connected == true) cout<<"Pomyslnie polaczono z serwerem";
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

void ConsoleClient::listenAndRecognize()
{
	while(!shutDown)
	{
		Message* m=nullptr;
		connectionManager->receive(serverip,m,55555);
		#ifdef _DEBUG
		cout<<"ConsoleClient::listenAndRecognize() coś odebrało"<<endl;
		#endif // _DEBUG
		m->print();
		if(m->getState()==(unsigned char)State::REQ)
		{
			if(m->getCategory()==(unsigned char)Category::PING)
			{
				pingMessage* pm1=new pingMessage(State::ACK);
				q.push_back(pm1);
			}
		}
		else if(m->getState()==(unsigned char)State::ACK)
		{
			/**< można by coś odesłać, a le w tej chwile nie ma to sensu */
		}
		anyResponse=true;
	}
}

void ConsoleClient::sendFromQueue()
{
	while(!shutDown)
	{
		Message* m=nullptr;
		m=q.pop_front();
		if(!shutDown)
		{
			connectionManager->send(serverip,*m,55555);
		}

	}
}












