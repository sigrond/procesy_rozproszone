/** \file Model.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy modelu
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "../protocol/Ip.hpp"

/** \brief klasa modelu
 */
class Model
{
public:
    Model();
    void setBlockingQueue(BlockingQueue<Event*>*);
    void pushTestEvents();
    void setController(void* c);
    void pushAddAgent(Ipv4& ip);
private:
    BlockingQueue<Event*>* blockingQueue;
	void* controller;
};

