/** \file AgentClient.cpp
 * \author Eryk Ratyński
 * \brief implementacja metod dla klasy AgentClient
 */

#include "AgentClient.hpp"
#include <string>
#include <thread>

using namespace message;
using namespace std;

AgentClient::AgentClient() : port(46000)
{

    connectionManager = ConnectionManager::getInstance(port);
	connected = false;
	working = false;
	shutDown = false;
	serverIP = new Ipv4(string("127.0.0.1"));
    q=new BlockingQueue<message::Message*>;

};

AgentClient::AgentClient(Ip &ip) : port(46000)
{
    connectionManager = ConnectionManager::getInstance(port);
	connected = false;
	working = false;
	shutDown = false;
	serverIP = &ip;
	q=new BlockingQueue<message::Message*>;
}

void AgentClient::start()
{
	//inicjalizacja polaczenia z serwerem
	thread clientThread(&AgentClient::sendFromQueue,this);
    while(!shutDown)
    {
     this->listen();
    }
};

void AgentClient::listen()
{
	message::Message *msg = nullptr;
	try
	{
        connectionManager->receive( *((Ipv4*)serverIP), msg);
	}
	catch(...)
	{
        #ifdef _DEBUG
        cout<<"wyjątek recive"<<endl;
        #endif // _DEBUG
        return;
	}
	#ifdef _DEBUG
	cout<<"odebraliśmy coś"<<endl;
	#endif // _DEBUG
	/** TO DO  rozszyfrowac wiadomosc */
	if (msg != nullptr)
	{
        std::thread readM(&AgentClient::readMsg, this, msg);

	}
};
void AgentClient::send( message::Message *msg)
{
    bool notSent=true;
    while(notSent)
    {
        try
        {
            connectionManager->send(*((Ipv4*)serverIP), *msg);
            notSent=false;
        }
        catch(...)
        {
            #ifdef _DEBUG
            cout<<"wyjątek send"<<endl;
            #endif // _DEBUG
        }
    }
};

void AgentClient::readMsg( message::Message *msg)
{
    #ifdef _DEBUG
    cout<<"AgentClient::readMsg( message::Message *msg)"<<endl;
    #endif // _DEBUG
    MessageParser messageParser(msg,q);
    messageParser.parse();

}

bool AgentClient::isConnected()
{
	return connected;
};
bool AgentClient::isWorking()
{
	return working;
};

void AgentClient::sendFromQueue()
{
    #ifdef _DEBUG
    cout<<"AgentClient::sendFromQueue()"<<endl;
    #endif // _DEBUG
    message::Message *msg = nullptr;
    while(!shutDown)
    {
        msg=q->pop_front();
        AgentClient::send(msg);
    }
}

