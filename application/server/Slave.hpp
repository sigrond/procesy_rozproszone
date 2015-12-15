/** \file Slave.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy Slave.
 *
 */

#pragma once

#include "Task.hpp"

/** \brief Klasa odpowiedzialna za przechowywanie informacji o agencie.
 */
class Slave
{
	public:
		/** Default constructor */
		Slave(Ip &ip);
		/** Default destructor */
		~Slave();
		/** Access slaveIP
		 * \return The current value of slaveIP
		 */
		IP* getSlaveIP() { return slaveIP; }
		/** Set slaveIP
		 * \param val New value to set
		 */
		void setSlaveIP(IP* val) { slaveIP = val; }
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
		Connection* getConnection() { return connection; }
		/** Set connection
		 * \param val New value to set
		 */
		void setConnection(Connection* val) { connection = val; }
		/** Access task
		 * \return The current value of task
		 */
		Task* getTask() { return task; }
		/** Set task
		 * \param val New value to set
		 */
		void setTask(Task* val) { task = val; }
	protected:
	private:
		IP* slaveIP;/**< adres agenta */
		time_t lastContact;/**< kiedy ostatnio agent odpowiedział */
		int state;/**< stan agenta */
		Connection* connection; //!< Member variable "connection"
		Task* task;/**< wskaźnik na aktualne zadanie */
		bool removed;/**< czy dostaliśmy polecenie usuniecia agenta */
};
