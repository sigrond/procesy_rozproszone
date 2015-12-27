/** \file Slave.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Slave.
 *
 */

#include "Slave.hpp"

Slave::Slave(Ip &ip) :
	slaveIP(&ip),
	lastContact(0),
	state(0),
	connectionManager(nullptr),
	task(nullptr),
	removed(false)
{
	connectionManager=ConnectionManager::getInstance();
}

Slave::~Slave()
{
	//dtor
}
