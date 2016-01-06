/** \file AgentClient.cpp
 * \author Eryk Ratyński
 * \brief implementacja metod dla klasy AgentClient
 */

#include "AgentClient.hpp"
#include <string>
using namespace message;
using namespace std;

AgentClient::AgentClient() : port(46000)
{

    connectionManager = ConnectionManager::getInstance(port);
	connected = false;
	working = false;
	shutDown = false;
	serverIP = new Ipv4(string("127.0.0.1"));


};

AgentClient::AgentClient(Ip &ip) : port(46000)
{
    connectionManager = ConnectionManager::getInstance(port);
	connected = false;
	working = false;
	shutDown = false;
	serverIP = &ip;
}

void AgentClient::start()
{
	//inicjalizacja polaczenia z serwerem
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
    MessageParser messageParser(msg);
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



