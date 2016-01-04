/** \file Slave.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy Slave.
 *
 */

#pragma once

#include "Task.hpp"
#include "../protocol/ConnectionManager.hpp"
#include <mutex>
#include <thread>

/** \brief Klasa odpowiedzialna za przechowywanie informacji o agencie.
 */
class Slave
{
private:
	Ip* slaveIP;/**< adres agenta */
	time_t lastContact;/**< kiedy ostatnio agent odpowiedział */
	int state;/**< stan agenta */
	ConnectionManager* connectionManager;
	Task* task;/**< wskaźnik na aktualne zadanie */
	bool removed;/**< czy dostaliśmy polecenie usuniecia agenta */
	bool listening;
public:
	/** Default constructor */
	Slave(Ip *ip, unsigned short portNo=55555);
	/** Default destructor */
	~Slave();
	/** Te setery i geterry zostały tu umieszczone automatycznie.
	 * Zostawiam je bo na razie nie wiadomo jak to do końca ma działać
	 * i pewnie finalnie tak zostaną. */
	/** Access slaveIP
	 * \return The current value of slaveIP
	 */
	Ip* getSlaveIP() { return slaveIP; }
	/** Set slaveIP
	 * \param val New value to set
	 */
	void setSlaveIP(Ip* val) { slaveIP = val; }
	/** Access lastContact
	 * \return The current value of lastContact
	 */
	time_t setLastContact() { return lastContact; }
	/** Set lastContact
	 * \param val New value to set
	 */
	void setLastContact(time_t val) { lastContact = val; }
	/** Access state
	 * \return The current value of state
	 */
	int getState() { return state; }
	/** Set state
	 * \param val New value to set
	 */
	void setState(int val) { state = val; }
	/** Access connection
	 * \return The current value of connection
	 */
	Task* getTask() { return task; }
	/** Set task
	 * \param val New value to set
	 */
	void setTask(Task* val) { task = val; }
	std::mutex listeningMutex;/**< to chyba znowu moja kolejna fanaberia */
	void setListening(bool);
	bool getListening();
	std::thread* slaveThread;
	bool ready;/**< gotowość na zadanie */
	unsigned short port;/**< numer portu na którym nasłuchuje agent */
protected:
};
