/** \file Controller.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Controller
 *
 */

#include "Controller.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

Controller::Controller() :
	adminServer(nullptr),
	agentServer(nullptr),
	blockingQueue(nullptr),
	strategyMap(nullptr),
	model(nullptr),
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

Controller::start()
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
	//tworzymy kolejkę komunikatów i mapę strategii
	blockingQueue=new BlockingQueue<Event*>;
	adminServer->setBlockingQueue(blockingQueue);
	agentServer->setBlockingQueue(blockingQueue);
	model->setBlockingQueue(blockingQueue);
	strategyMap=new std::map<EventType,Strategy*>;
	fillStrategyMap();

	/**< \todo uruchomić adminServer i agentServer, timery w modelu i inne */

	//pętla przetwarzania komunikatów / zdarzeń
	Event* e=nullptr;
	while(!shutDownServer)
	{
		e=blockingQueue.pop_front();
		strategyMap->at(e->type)->doJob(e->data);
		delete e;
	}
}

Controller::fillStrategyMap()
{
	if(strategyMap==nullptr)
	{
		throw ControllerException("strategyMap==nullptr");
	}
	strategyMap->insert(std::pair<EventType,Strategy*>(Test,new TestStrategy()));
	strategyMap->insert(std::pair<EventType,Strategy*>(SHUT_DOWN,new ShutDownStrategy()));
	/**< \todo wstawić więcej strategii, ustalić w którym pliku powinny znajdować się strategie i je napisać */
}

/** \brief Metoda ustawia zmienną prywatną shutDownServer na zamykanie serwera.
 */
Controller::triggerShutDown()
{
	shutDownServer=true;
}



























