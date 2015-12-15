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
	AdminServerExceptionException(std::string s)
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
	connection(nullptr),
	adminIP(nullptr)
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::AdminServer()\n";
	#endif // _DEBUG
	connection=new Connection();
}

AdminServer::AdminServer(Ip &ip) :
	blockingQueue(nullptr),
	connection(nullptr)
	adminIP(nullptr)
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::AdminServer(Ip &ip)\n";
	#endif // _DEBUG
	connection=new Connection(ip);
	adminIP=&ip;
}

AdminServer::~AdminServer()
{
	#ifdef _DEBUG
	std::clog<<"AdminServer::~AdminServer()\n";
	#endif // _DEBUG
	if(connection!=nullptr)
	{
		delete connection;
	}
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
	m=connection->receive();
	blockingQueue->push_back(new Event(MESSAGE_FROM_ADMIN_SERVER,m));
}

void AdminServer::connect(message::Message* m)
{
	connection->send(*m);
}

void AdminServer::setBlockingQueue(BlockingQueue<Event*>* q)
{
	blockingQueue=q;
}
