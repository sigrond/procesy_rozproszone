/** \file ConsoleClient.cpp
 * \authors Tomasz Jakubczyk, Kacper Stachyra
 * \brief Implementacje metod klasy ConsoleClient
 *
 */


#include "ConsoleClient.hpp"
#include <thread>
#include <chrono>

extern bool demo;


//maksymalna liczna polecenia + argumentow
#define ARGS 3

using namespace std;
using namespace message;

ConsoleClient::ConsoleClient() : shutDown(false),taskCount(0)
{
    connected = false;
    requestAnswered = 1;
    connectionManager=ConnectionManager::getInstance(55000);
    serverip=Ipv4("127.0.0.1");
}

void ConsoleClient::start()
{
    thread listenAndRecognizeThread(&ConsoleClient::listenAndRecognize,this);
    thread sendFromQueueThread(&ConsoleClient::sendFromQueue,this);

    string arg[ARGS];

    int command=NC;
    fileAck=false;
    hostAck=false;
    int licz=0;

    while(!shutDown)
    {

        if(demo && licz<=3)
        {
        	command=CON;
        	arg[1]="127.0.0.1";
        	if(connected && !hostAck)
        	{
                command=ADD_AGENT;
                arg[1]="127.0.0.1";
        	}
        	if(connected && hostAck)
			{
				command=ADD;
				arg[1]="test";//teoretyczny plik zadania
				if(licz<3)
				{
					licz++;
				}
			}
        }
        else
		{
			cout<<"Wpisz polecenie."<<endl;
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
                anyResponse=false;
                pingAck=false;
                pingMessage* m1=new pingMessage(message::State::REQ);
                Message* m2=nullptr;
                pingMessage* m3=new pingMessage(message::State::ACK);
                pingMessage* m4=new pingMessage(message::State::OK);
                q.push_back(m1);
                #ifdef _DEBUG
                cout<<"ping do serwera LOTC wysłany"<<endl;
                #endif // _DEBUG
				while(!anyResponse);
				if(pingAck)
				{
					q.push_back(m4);
				}
				connected=true;
                if (connected == true) cout<<"Pomyslnie polaczono z serwerem\n";
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
                pingMessage* m1=new pingMessage(message::State::REQ);
                fileAck=false;
                fileMessage* fm=new fileMessage(State::REQ,true,++taskCount,arg[1]);
                #ifdef _DEBUG
                cout<<"wysyłam plik"<<endl;
                #endif // _DEBUG
                q.push_back(fm);
                unsigned long long stoper=0;
                while(!fileAck && stoper<=3000000000)
				{
					stoper++;
					if(stoper>2000000000)
					{
						stoper=0;
						#ifdef _DEBUG
						cout<<"wysyłam dodatkowy ping REQ, bo coś nie widzę odpowiedzi o pliku i powtarzam przesłanie pliku"<<endl;
						#endif // _DEBUG
						q.push_back(m1);
						q.push_back(fm);
					}
				}
                taskAck=false;
                taskMessage* tm=new taskMessage(TaskSub::T_ADD,State::REQ,false,0,taskCount,chrono::steady_clock::now());
                #ifdef _DEBUG
                cout<<"wysyłam zadanie ADD"<<endl;
                #endif // _DEBUG
                q.push_back(tm);
                while(!fileAck && stoper<=3000000000)
				{
					stoper++;
					if(stoper>2000000000)
					{
						stoper=0;
						q.push_back(fm);
					}
				}
                taskAck=false;
                tm=new taskMessage(TaskSub::T_RUN,State::REQ,false,0,taskCount,chrono::steady_clock::now());
                #ifdef _DEBUG
                cout<<"wysyłam zadanie RUN"<<endl;
                #endif // _DEBUG
                q.push_back(tm);
                while(!fileAck && stoper<=3000000000)
				{
					stoper++;
					if(stoper>2000000000)
					{
						stoper=0;
						q.push_back(fm);
					}
				}
                cout<<"zadanie zlecone"<<endl;
                cout<<"==============================================================================================================================="<<endl;
                cout<<"==============================================================================================================================="<<endl;
                std::this_thread::sleep_for (std::chrono::milliseconds(1000));
            }
            else
            {
                cout<<"Brak polaczenia z serwerem\n";
            }
        }
        else if(command == ADD_AGENT)
        {
            if (connected)
            {
                hostMessage* hm=nullptr;
                Ipv4* ip=new Ipv4(arg[1]);
                vector<Ipv4>* a=new vector<Ipv4>;
                a->push_back(*ip);
                hm=new hostMessage(HostSub::H_ADD,State::REQ,*a);

                pingMessage* m1=new pingMessage(message::State::REQ);
                hostAck=false;
                //fileMessage* fm=new fileMessage(State::REQ,true,++taskCount,arg[1]);
                #ifdef _DEBUG
                cout<<"wysyłam namiary hosta"<<endl;
                #endif // _DEBUG
                q.push_back(hm);
                unsigned long long stoper=0;
                while(!hostAck && stoper<=3000000000)
				{
					stoper++;
					if(stoper>2000000000)
					{
						stoper=0;
						#ifdef _DEBUG
						cout<<"wysyłam dodatkowy ping REQ, bo coś nie widzę odpowiedzi o ADD HOST i powtarzam przesłanie ADD HOST"<<endl;
						#endif // _DEBUG
						q.push_back(m1);
						q.push_back(hm);
					}
				}
                //hostAck=false;
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
    else if(arg[0].compare("add")==0) command = ADD;
    else if(arg[0].compare("add_agent")==0) command = ADD_AGENT;

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
		try
		{
            connectionManager->receive(serverip,m,55555);
		}
		catch(...)
		{
            #ifdef _DEBUG
            cout<<"wyjątek z recive, powtarzam"<<endl;
            #endif // _DEBUG
            continue;
		}
		#ifdef _DEBUG
		cout<<"ConsoleClient::listenAndRecognize() coś odebrało"<<endl;
		#endif // _DEBUG
		m->print();
		if(m->getState()==(unsigned char)State::REQ)
		{
			if(m->getCategory()==(unsigned char)Category::PING)
			{
				#ifdef _DEBUG
				cout<<"odebrane ping REQ, odsyłamy ACK"<<endl;
				#endif // _DEBUG
				pingMessage* pm1=new pingMessage(State::ACK);
				q.push_back(pm1);
			}
			if(m->getCategory()==(unsigned char)Category::RET)
			{
				cout<<"dostaliśmy wynik zadania"<<endl;
				m->print();
			}
		}
		else if(m->getState()==(unsigned char)State::ACK)
		{
			if(m->getCategory()==(unsigned char)Category::PING)
			{
				#ifdef _DEBUG
				cout<<"odebrane ping ACK"<<endl;
				#endif // _DEBUG
			}
			/**< można by coś odesłać, a le w tej chwile nie ma to sensu */
			if(m->getCategory()==(unsigned char)Category::FILE)
			{
				#ifdef _DEBUG
				cout<<"odebrane file ACK"<<endl;
				#endif // _DEBUG
				fileAck=true;
			}
			if(m->getCategory()==(unsigned char)Category::TASK)
			{
				#ifdef _DEBUG
				cout<<"odebrane task ACK"<<endl;
				#endif // _DEBUG
				taskAck=true;
			}
			if(m->getCategory()==(unsigned char)Category::HOST)
			{
				#ifdef _DEBUG
				cout<<"odebrane host ACK"<<endl;
				#endif // _DEBUG
				hostAck=true;
			}
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
            try
            {
                connectionManager->send(serverip,*m,55555);
            }
            catch(...)
            {
                #ifdef _DEBUG
                cout<<"wyjątek send, powtarzam"<<endl;
                #endif // _DEBUG
                continue;
            }
			#ifdef _DEBUG
			cout<<"coś wysłano"<<endl;
			#endif // _DEBUG
		}

	}
}












