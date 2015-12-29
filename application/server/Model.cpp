/** \file Model.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami metod klasy modelu
 *
 */

#include "Model.hpp"
#include "Event.hpp"
#include "Controller.hpp"
#include "../protocol/Ip.hpp"
#include <exception>
#include <utility>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

/** \brief Klasa opakowująca exception dla Model
 */
struct ModelException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	ModelException(std::string s)
	{
		m="ModelException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

Model::Model() :
	blockingQueue(nullptr),
	controller(nullptr),
	shutDown(false)
{

}

void Model::setBlockingQueue(BlockingQueue<Event*>* q)
{
	blockingQueue=q;
}

void Model::setController(void* c)
{
	controller=c;
}

void Model::pushTestEvents()
{
	if(blockingQueue==nullptr)
	{
		throw ModelException("brak kolejki");
	}
	blockingQueue->push_back(new Event());
	blockingQueue->push_back(new Event(Test));
	blockingQueue->push_back(new Event(Test,nullptr));
	blockingQueue->push_back(new Event(SHUT_DOWN,controller));
}

void Model::pushAddAgent(Ipv4& ip)
{
	if(blockingQueue==nullptr)
	{
		throw ModelException("brak kolejki");
	}
	if(controller==nullptr)
	{
		throw ModelException("brak kontrolera");
	}
	pair<void*,void*>* p=nullptr;
	p=new pair<void*,void*>((void*)&ip,(void*)controller);
	blockingQueue->push_back(new Event(ADD_AGENT,p));
}

void Model::pingAdmin()
{
	shutDown=false;
	std::unique_lock<std::mutex> lck(adminPingMutex);
    while(!shutDown)
	{
		adminPingCond.wait_for(lck ,chrono::seconds(10));
        blockingQueue->push_back(new Event(PING_ADMIN,nullptr));
	}
}

/** \brief metoda zlecająca odpytanie agentów
 * na chwilę obecną nie rozdzielam odpytywania agentów
 * \return void
 *
 */
void Model::pingSlaves()
{
	shutDown=false;
	std::unique_lock<std::mutex> lck(slavesPingMutex);
    while(!shutDown)
	{
		slavesPingCond.wait_for(lck ,chrono::seconds(11));
        blockingQueue->push_back(new Event(PING_SLAVES,nullptr));
	}
}

void Model::triggerShutDown()
{
	shutDown=true;
}

























