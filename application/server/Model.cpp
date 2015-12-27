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

Model::Model()
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

























