/** \file Model.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy modelu
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"

/** \brief klasa modelu
 */
class Model
{
public:
    Model();
    void setBlockingQueue(BlockingQueue<Event*>*);
    void pushTestEvents();
    void setController(void* c);
private:
    BlockingQueue<Event*>* blockingQueue;
	void* controller;
};

