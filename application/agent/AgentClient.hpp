/** \file AgentClient.hpp
 * \author Eryk Raty�ski
 * \brief Plik nag��wkowy klienta dla agenta
 */

#ifndef AgentClient_hpp
#define AgentClient_hpp

class AgentClient
{
public:
	AgentClient();

	/** metoda inicjalizuje po��czenie z serwerem */
	void start();

	
	bool isConnected();
	bool isWorking();

private:
	/**pole przechowuje informacje czy agent jest po��czony z serwerem */
	bool connected;

	/** pole przechowuje informacje czy agent jest w trakcie wykonywania jakiegos zadania */
	bool working;


	/** metoda nas�uchuj�ca na komunikaty z serwera*/
	void listen();

	/** metoda wysy�aj�ca komunikat do serwera */
	void send( void* msg);
};

#endif