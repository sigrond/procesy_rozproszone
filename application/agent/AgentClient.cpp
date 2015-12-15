/** \file AgentClient.cpp
 * \author Eryk Ratyñski
 * \brief implementacja metod dla klasy AgentClient
 */

#include "AgentClient.hpp"


AgentClient::AgentClient()
{
	connected = false;
	working = false;
};

void AgentClient::start()
{
	//inicjalizacja polaczenia z serwerem

	//this->listen();
};

void AgentClient::listen()
{
	
};
void AgentClient::send( void* msg)
{
	
};

bool AgentClient::isConnected()
{
	return connected;
};
bool AgentClient::isWorking()
{
	return working;
};