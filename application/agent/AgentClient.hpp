/** \file AgentClient.hpp
 * \authors Eryk Ratyński, Tomasz Jakubczyk
 * \brief Plik nagłówkowy klienta dla agenta
 * \date 12 gru 2015
 * Low Orbit Task Cannon
 */
#ifndef AgentClient_hpp
#define AgentClient_hpp

#include "../protocol/ConnectionManager.hpp"
#include "../server/BlockingQueue.hpp"
#include "MessageParser.hpp"

#include <thread>
#include <iostream>


class AgentClient
{
public:
	AgentClient();
	AgentClient(Ip &ip);

	/** metoda inicjalizuje połączenie z serwerem */
	void start();


	bool isConnected();
	bool isWorking();

private:
    ConnectionManager *connectionManager;

    /** IP serwera, do którego łączy się agent */
    Ip *serverIP;

	/**pole przechowuje informacje czy agent jest połączony z serwerem */
	bool connected;

	/** pole przechowuje informacje czy agent jest w trakcie wykonywania jakiegos zadania */
	bool working;

    /** pole przechowuje informacje, czy agent jest zamykany */
	bool shutDown;


	/** metoda nasłuchująca na komunikaty z serwera*/
	void listen();

	/** metoda wysyłająca komunikat do serwera */
	void send( message::Message *msg);

	/**metoda czytająca kod wiadomości, na jego podstawie wywołuje odpowiednie funkcje*/
	void readMsg (message::Message *msg);

    unsigned short port;

    BlockingQueue<message::Message*>* q;

    void sendFromQueue();

};


#endif
