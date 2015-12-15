/** \file Controller.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Controller
 *
 */

#include "Controller.hpp"
#include "Strategies.hpp"
#include "Event.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

Controller::Controller() :
	alive(0),
	adminServer(nullptr),
	agentServer(nullptr),
	model(nullptr),
	blockingQueue(nullptr),
	strategyMap(nullptr),
	shutDownServer(false)
{
#ifdef _DEBUG
	std::cout<<"Controller::Controller()\n";
#endif // _DEBUG
}

Controller::~Controller()
{
	/*
	na wszelki wypadek usuwamy wszystko co jeszcze nie zostało usunięte.
	chyba nie chcielibyśmy, żeby jakiś nowy kontroler użył starych śmieci
	*/
	if(adminServer!=nullptr)
	{
		delete adminServer;
	}
	if(agentServer!=nullptr)
	{
		delete agentServer;
	}
	if(blockingQueue!=nullptr)
	{
		delete blockingQueue;
	}
	if(strategyMap!=nullptr)
	{
		delete strategyMap;
	}
	if(model!=nullptr)
	{
		delete model;
	}
}

/** \brief Klasa opakowująca exception dla Controller
 */
struct ControllerException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	ControllerException(std::string s)
	{
		m="ControllerException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

void Controller::start()
{
	/*czy wszystko jest?
	jeśli nie, to wywalamy się z gracją*/
	if(adminServer==nullptr)
	{
		throw ControllerException("adminServer==nullptr");
	}
	if(agentServer==nullptr)
	{
		throw ControllerException("agentServer==nullptr");
	}
	if(model==nullptr)
	{
		throw ControllerException("model==nullptr");
	}
	if(blockingQueue==nullptr)
	{
		throw ControllerException("blockingQueue==nullptr");
	}
	alive++;
	//tworzymy mapę strategii
	strategyMap=new std::map<EventType,Strategy*>;
	fillStrategyMap();

	/**< \todo uruchomić adminServer i agentServer, timery w modelu i inne */

	//pętla przetwarzania komunikatów / zdarzeń
	Event* e=nullptr;
	while(!shutDownServer)
	{
		e=blockingQueue->pop_front();
		std::cout<<this<<" "<<e->data<<std::endl;
		strategyMap->at(e->type)->doJob(e->data);
		delete e;
		//int a;
		//std::cin>>a;
		//if(a==0) break;
	}
	alive--;
}

void Controller::fillStrategyMap()
{
	if(strategyMap==nullptr)
	{
		throw ControllerException("strategyMap==nullptr");
	}
	strategyMap->insert(std::pair<EventType,Strategy*>(Test,new TestStrategy()));
	strategyMap->insert(std::pair<EventType,Strategy*>(SHUT_DOWN,new ShutDownStrategy()));
	strategyMap->insert(std::pair<EventType,Strategy*>(MESSAGE_FROM_ADMIN_SERVER,new MessageFromAdminStrategy()));
	strategyMap->insert(std::pair<EventType,Strategy*>(MESSAGE_FROM_AGENT_SERVER,new MessageFromAgentStrategy()));
	/**< \todo wstawić więcej strategii, ustalić w którym pliku powinny znajdować się strategie i je napisać */
}

/** \brief Metoda ustawia zmienną prywatną shutDownServer na zamykanie serwera.
 * Użycie metody poza strategią obsługi zadań może prowadzić do zakleszcznia!
 * Metoda nie potrafi samodzielnie zamknąć serwera, bo nie przerywa oczekiwania na
 * metodzie BlockingQueue::popfront() i nie przerwie pętli przetważania, dopuki
 * wątek oczekuje na pojawienie się elementu w kolejce.
 * EDIT: Już powinna sobie dać radę z kolejką blokującą.
 */
void Controller::triggerShutDown()
{
	shutDownServer=true;
	if(blockingQueue!=nullptr)
	{
		blockingQueue->push_back(new Event(SHUT_DOWN,this));
	}
}

void Controller::setAdminServer(AdminServer* s)
{
	adminServer=s;
}

void Controller::setAgentServer(AgentServer* s)
{
	agentServer=s;
}

void Controller::setModel(Model* m)
{
	model=m;
}

void Controller::setup()
{
	if(adminServer==nullptr)
	{
		throw ControllerException("adminServer==nullptr");
	}
	if(agentServer==nullptr)
	{
		throw ControllerException("agentServer==nullptr");
	}
	if(model==nullptr)
	{
		throw ControllerException("model==nullptr");
	}
	//tworzymy kolejkę komunikatów
	blockingQueue=new BlockingQueue<Event*>;
	adminServer->setBlockingQueue(blockingQueue);
	agentServer->setBlockingQueue(blockingQueue);
	model->setBlockingQueue(blockingQueue);
	model->setController(this);
}























