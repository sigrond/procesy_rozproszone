/** \file Model.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami metod klasy modelu
 *
 */

#include "Model.hpp"
#include "Event.hpp"
#include <exception>

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
		throw "brak kolejki";
	}
	blockingQueue->push_back(new Event());
	blockingQueue->push_back(new Event(Test));
	blockingQueue->push_back(new Event(Test,nullptr));
	blockingQueue->push_back(new Event(SHUT_DOWN,controller));
}


























