/** \file Slave.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Slave.
 * \date
 * Low Orbit Task Cannon
 */

#include "Slave.hpp"

Slave::Slave(Ip* ip, unsigned short portNo) :
	slaveIP(ip),
	lastContact(0),
	state(0),
	connectionManager(nullptr),
	task(nullptr),
	removed(false),
	listening(false),
	slaveThread(nullptr),
	ready(false),
	port(portNo)
{
	connectionManager=ConnectionManager::getInstance();
}

Slave::~Slave()
{
	if(slaveThread!=nullptr)
	{
		delete slaveThread;
	}
}

void Slave::setListening(bool b)
{
	listeningMutex.lock();
	listening=b;
	listeningMutex.unlock();
}
bool Slave::getListening()
{
	bool b=false;
	listeningMutex.lock();
	b=listening;
	listeningMutex.unlock();
	return b;
}












