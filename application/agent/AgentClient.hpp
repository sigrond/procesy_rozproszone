/** \file AgentClient.hpp
 * \author Eryk Ratyñski
 * \brief Plik nag³ówkowy klienta dla agenta
 */

#ifndef AgentClient_hpp
#define AgentClient_hpp

class AgentClient
{
public:
	AgentClient();

	/** metoda inicjalizuje po³¹czenie z serwerem */
	void start();

	
	bool isConnected();
	bool isWorking();

private:
	/**pole przechowuje informacje czy agent jest po³¹czony z serwerem */
	bool connected;

	/** pole przechowuje informacje czy agent jest w trakcie wykonywania jakiegos zadania */
	bool working;


	/** metoda nas³uchuj¹ca na komunikaty z serwera*/
	void listen();

	/** metoda wysy³aj¹ca komunikat do serwera */
	void send( void* msg);
};

#endif