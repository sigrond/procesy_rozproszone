/** \file AdminServer.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami klasy serwera administratora
 *
 */

#include "AdminServer.hpp"
#include <exception>
#include <iostream>

/** \brief Klasa opakowująca exception dla AdminServer
 */
struct AdminServerException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	AdminServerException(std::string s)
	{
		m="AdminServerException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

AdminServer::AdminServer() :
	blockingQueue(nullptr),
	connectionManager(nullptr),
	adminIP(nullptr),
	shutDown(false)
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::AdminServer()\n";
	#endif // _DEBUG
	connectionManager=ConnectionManager::getInstance();
}

AdminServer::AdminServer(Ip &ip) :
	blockingQueue(nullptr),
	connectionManager(nullptr),
	adminIP(nullptr)
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::AdminServer(Ip &ip)\n";
	#endif // _DEBUG
	connectionManager=ConnectionManager::getInstance();
	adminIP=&ip;
}

AdminServer::~AdminServer()
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::~AdminServer()\n";
	#endif // _DEBUG
	/*if(connection!=nullptr)
	{
		delete connection;
	}*/
	if(adminIP!=nullptr)
	{
		delete adminIP;
	}
}

void AdminServer::listen()
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::listen()\n";
	#endif // _DEBUG
	message::Message* m=nullptr;
	//m=connection->receive();
	connectionManager->receive(*static_cast<Ipv4*>(adminIP),m);/**< \todo co się stanie jak nie znamy adresu admina? */
	blockingQueue->push_back(new Event(MESSAGE_FROM_ADMIN_SERVER,m));
}

void AdminServer::connect(message::Message* m)
{
	connectionManager->send(*static_cast<Ipv4*>(adminIP),*m);
}

void AdminServer::setBlockingQueue(BlockingQueue<Event*>* q)
{
	blockingQueue=q;
}

void AdminServer::start()
{
	/**< \todo sprawdzenia i wyjątki */
	shutDown=false;
    while(!shutDown)
	{
		listen();
	}
}

void AdminServer::triggerShutDown()
{
	shutDown=true;
}























