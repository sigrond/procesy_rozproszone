/** \file AgentClient.cpp
 * \author Eryk Ratyński
 * \brief implementacja metod dla klasy AgentClient
 */

#include "AgentClient.hpp"
using namespace message;

AgentClient::AgentClient()
{

    connectionManager = ConnectionManager::getInstance();
	connected = false;
	working = false;
	shutDown = false;
	serverIP = nullptr;


};

AgentClient::AgentClient(Ip &ip)
{
    connectionManager = ConnectionManager::getInstance();
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
	connectionManager->receive( *((Ipv4*)serverIP), msg);
	/** TO DO  rozszyfrowac wiadomosc */
	if (msg != nullptr)
	{
        std::thread readM(&AgentClient::readMsg, this, msg);

	}
};
void AgentClient::send( message::Message *msg)
{
	connectionManager->send(*((Ipv4*)serverIP), *msg);
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



