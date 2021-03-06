/** \file Model.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy modelu
 * \date 21 Nov 2015
 * Low Orbit Task Cannon
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "../protocol/Ip.hpp"
#include "Task.hpp"
#include <mutex>
#include <condition_variable>
#include <string>

/** \brief klasa modelu
 */
class Model
{
public:
    Model();
    void setBlockingQueue(BlockingQueue<Event*>*);
    void pushTestEvents();
    void setController(void* c);
    void pushAddAgent(Ipv4* ip, unsigned short port=55555);
    void pingAdmin();/**< pingowanie okresowo i na ewentualne żądanie */
    void pingSlaves();
    void triggerShutDown();
    void addTask(std::string s);
private:
    BlockingQueue<Event*>* blockingQueue;
	void* controller;
	bool shutDown;
	std::mutex adminPingMutex;
	std::condition_variable adminPingCond;
	std::mutex slavesPingMutex;
	std::condition_variable slavesPingCond;
};

