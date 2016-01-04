/** \file Controller.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Controller
 *
 */

#include "Strategies.hpp"
#include "Controller.hpp"
#include "Event.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

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
		adminServer=nullptr;
	}
	if(agentServer!=nullptr)
	{
		delete agentServer;
		agentServer=nullptr;
	}
	if(blockingQueue!=nullptr)
	{
		delete blockingQueue;
		blockingQueue=nullptr;
	}
	if(strategyMap!=nullptr)
	{
		delete strategyMap;
		strategyMap=nullptr;
	}
	if(model!=nullptr)
	{
		delete model;
		model=nullptr;
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
	shutDownServer=false;/**< jeśli chcielibyśmy wielokrotnie zamykać i uruchamiać srwer */
	alive++;
	//tworzymy mapę strategii
	strategyMap=new std::map<EventType,Strategy*>;
	fillStrategyMap();

	thread adminServerThread(&AdminServer::start,adminServer);
	thread agentServerThread(&AgentServer::start,agentServer);
	thread pingAdminThread(&Model::pingAdmin,model);
	thread pingSlavesThread(&Model::pingSlaves,model);

	/**< \todo uruchomić adminServer i agentServer, timery w modelu i inne */

	//pętla przetwarzania komunikatów / zdarzeń
	Event* e=nullptr;
	while(!shutDownServer)
	{
		e=blockingQueue->pop_front();
		std::cout<<this<<" "<<e->data<<std::endl;
		strategyMap->at(e->type)->doJob(e->data,e->who,e->port);
		delete e;
		//int a;
		//std::cin>>a;
		//if(a==0) break;
	}
	alive--;
	mutex mtx;/**< strzelba na mrówki */
	std::unique_lock<std::mutex> lck(mtx);/**< just for fun */
	//lck.lock();
	condition_variable c;/**< bo mikro-slip działa źle */
	cout<<"terminate threads in: 10, ";
	cout.flush();
	//lck.unlock();
	for(int i=9;i>=0;i--)
	{
		c.wait_for(lck ,chrono::seconds(1));/**< KABOOM! */
		//lck.lock();
		cout<<i<<", ";
		cout.flush();
		//lck.unlock();
	}
	cout<<endl<<"terminate"<<endl;
	pingAdminThread.join();/**< ten join powinien się udać */
	cout<<"pingAdminThread.join()"<<endl;
	//throw ControllerException("zamykamy budę!");
	adminServerThread.~thread();/**< zdychaj gnido! */
	adminServerThread.join();
	cout<<"adminServerThread.join()"<<endl;
	agentServerThread.join();
	cout<<"agentServerThread.join()"<<endl;
	//agentServerThread.~thread();/**< tu program nie dojdzie */
	cout<<"terminated?"<<endl;

}

void Controller::fillStrategyMap()
{
	if(strategyMap==nullptr)
	{
		throw ControllerException("strategyMap==nullptr");
	}
	strategyMap->insert(std::pair<EventType,Strategy*>(Test,new TestStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(SHUT_DOWN,new ShutDownStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(MESSAGE_FROM_ADMIN_SERVER,new MessageFromAdminStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(MESSAGE_FROM_AGENT_SERVER,new MessageFromAgentStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(ADD_AGENT,new AddAgentStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(PING_ADMIN,new PingAdminStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(PING_SLAVES,new PingSlavesStrategy(this)));
	strategyMap->insert(std::pair<EventType,Strategy*>(ADD_TASK,new AddTaskStrategy(this)));

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
		//dodatkowy komunikat, żeby odblokować kolejkę
		blockingQueue->push_back(new Event(SHUT_DOWN,this));
	}
	if(model!=nullptr)
	{
		model->triggerShutDown();
	}
	if(adminServer!=nullptr)
	{
		adminServer->triggerShutDown();
	}
	if(agentServer!=nullptr)
	{
		agentServer->triggerShutDown();
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























