/** \file AgentClient.hpp
 * \author Eryk Ratyński
 * \brief Plik nagłówkowy klienta dla agenta
 */

#ifndef AgentClient_hpp
#define AgentClient_hpp

class AgentClient
{
public:
	AgentClient();

	/** metoda inicjalizuje połączenie z serwerem */
	void start();

	
	bool isConnected();
	bool isWorking();

private:
	/**pole przechowuje informacje czy agent jest połączony z serwerem */
	bool connected;

	/** pole przechowuje informacje czy agent jest w trakcie wykonywania jakiegos zadania */
	bool working;


	/** metoda nasłuchująca na komunikaty z serwera*/
	void listen();

	/** metoda wysyłająca komunikat do serwera */
	void send( void* msg);
};

#endif