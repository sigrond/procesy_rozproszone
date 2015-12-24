/** 
 * \file ConnectioniManager.cpp
 *
 * \brief  Plik z implementacjami metod klasy ConnectionManager
 *
 * \author Andrzej Roguski
 */
#include <typeinfo>
#include <thread>

#include "ConnectionManager.hpp"


#include <iostream>

#define DBG(x) std::cout << x << std::endl;

void awaitConnections( ConnectionManager * conMan )
{
        DBG("awaitConnections()")

        int socket;

        while( true )
        {
                socket = conMan->listeningSocket->accept();

                Ipv4 ip = conMan->listeningSocket->getIp();
                
                DBG("accepted " << conMan->listeningSocket->getIp().getAddress() )

                Connection * connection = conMan->map4[ip];

                if( connection == nullptr )
                        connection = new Connection( socket );
        }
}


// tak, to działa i jest bezpieczne wątkowo (Magic Statics)
// C++11 takie piękne
ConnectionManager * ConnectionManager::getInstance()
{
        static ConnectionManager instance;
        return &instance;  
}

ConnectionManager::ConnectionManager()
{
        listeningSocket = new SocketIp4( Ipv4() );

        try
        {
                std::cout << "Bind: " << listeningSocket->bind() << std::endl;
                std::cout << "Listen: " << listeningSocket->listen() << std::endl;
        }
        catch (std::exception & e)
        {
                std::cerr << e.what() << std::endl;
        }

        std::thread ( awaitConnections, this ).detach();
}

ConnectionManager::~ConnectionManager()
{

}

void ConnectionManager::send( const Ipv4 & ip, const message::Message & msg )
{
        DBG("ConMan::send()")
        Connection * connection = map4[ip];

        if( connection == nullptr )
        {
                DBG("CM::s() connection not found, new connection")
                connection = new Connection( ip );
        }
        
        connection->send(msg);
}

void ConnectionManager::receive( const Ipv4 & ip, message::Message * const msg )
{
        DBG("ConMan::receive()")
        Connection * connection = map4[ip];

        if( connection == nullptr )
        {
                DBG("CM::r() connection not found, new connection")
                connection = new Connection( ip );
        }
        
        connection->receive(msg);

}

void ConnectionManager::remove( const Ipv4 & ip )
{

}

void ConnectionManager::send( const Ipv6 & ip, const message::Message & msg )
{

}

void ConnectionManager::receive( const Ipv6 & ip, message::Message * const msg )
{

}

void ConnectionManager::remove( const Ipv6 & ip )
{

}
