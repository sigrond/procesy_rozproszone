/** \file AgentServer.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami metod klasy serwera klienta / agenta
 *
 */

#include "AgentServer.hpp"
#include <exception>
#include <iostream>
#include <thread>

/** \brief Klasa opakowująca exception dla AgentServer
 */
struct AgentServerException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	AgentServerException(std::string s)
	{
		m="AgentServerException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

AgentServer::AgentServer() :
	blockingQueue(nullptr),
	slaves(nullptr),
	shutDown(false)
{
	slaves=new std::vector<Slave*>();
}

AgentServer::~AgentServer()
{
	if(slaves!=nullptr)
	{
		for(unsigned int i=0;i<slaves->size();i++)
		{
			if(slaves->at(i)!=nullptr)
			{
				delete slaves->at(i);
				slaves->at(i)=nullptr;/** przezorny zawsze ubezpieczony :D
										* BTW na pewno gdzieś w okolicach tego regionu
										* kodu będą problemy. więc:
										* \todo testy jednostkowe! :) */
			}
		}
		delete slaves;
	}
}

void AgentServer::connect(Slave* who, message::Message* m)
{
	who->getConnection()->send(*m);/**< \todo dodać jakiś zabezpieczeń bo groźnie to wygląda */
}

void AgentServer::listen(Slave* who)
{
	message::Message* m=nullptr;
	m=who->getConnection()->receive();
	blockingQueue->push_back(new Event(MESSAGE_FROM_AGENT_SERVER,m));
}

void AgentServer::setBlockingQueue(BlockingQueue<Event*>* q)
{
	blockingQueue=q;
}

void AgentServer::addSlave(Ip &ip)
{
	if(slaves==nullptr)
	{
		throw AgentServerException("slaves==nullptr");
	}
	slaves->push_back(new Slave(ip));
}

void AgentServer::listenToAll()/**< \todo dobrze przemyśleć jak ma działać */
{
	std::thread* t;/**< \todo ? wątki tutaj potrzebne? */
	for(unsigned int i=0;i<slaves->size();i++)
	{
		listen(slaves->at(i));/**< \todo jakiś if, bo jak się doda nowy to co */
	}
}

void AgentServer::start()
{

}


























