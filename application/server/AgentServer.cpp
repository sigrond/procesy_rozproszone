/** \file AgentServer.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami metod klasy serwera klienta / agenta
 *
 */

#include "AgentServer.hpp"

AgentServer::AgentServer()
{

}

void AgentServer::connect(void* who)
{

}

void AgentServer::listen()
{

}

void AgentServer::setBlockingQueue(BlockingQueue<Event*>* q)
{
	blockingQueue=q;
}
