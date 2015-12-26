/** 
 * \file ConnectioniManager.cpp
 *
 * \brief  Plik z implementacjami metod klasy ConnectionManager
 *
 * \author Andrzej Roguski
 */
#include <typeinfo>
#include <thread>
#include <iostream>

#include "ConnectionManager.hpp"

#include "debug.h"

void awaitConnections( ConnectionManager * conMan )
{
        DBG("awaitConnections()")

        int socket;

        while( true )
        {
                socket = conMan->listeningSocket->accept();

                Ipv4 ip = conMan->listeningSocket->getIp();
                
                DBG("accepted " << conMan->listeningSocket->getIp().getAddress() )
                
                conMan->map4Mutex.lock();

                        Connection * connection = conMan->map4[ip];

                        if( connection == nullptr )
                        {
                                DBG("awaitConnections(): connection not found, new connection")
                                connection = new Connection( socket );

                                try
                                {
                                        std::condition_variable & conVar = conMan->receiveGuards.at( ip );

                                        conVar.notify_one();

                                        delete &conVar;

                                        conMan->receiveGuards.erase( ip );
                                }
                                catch( std::out_of_range e)
                                {
                                        // nic, po protu nikt nie czeka na wiadomość z adresu IP == ip
                                }
                        }

                conMan->map4Mutex.unlock();
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
        DBG("ConnectionManager()")
        listeningSocket = new SocketIp4( Ipv4() );

        try
        {
                listeningSocket->bind();
                listeningSocket->listen();
        }
        catch (std::exception & e)
        {
                std::cerr << e.what() << std::endl;
        }

        std::thread ( awaitConnections, this ).detach();
}

ConnectionManager::~ConnectionManager()
{
        DBG("~ConnectionManager()")
}

void ConnectionManager::send( const Ipv4 & ip, const message::Message & msg )
{
        DBG("ConMan::send( " << ip.getAddress() << " )")

        map4Mutex.lock();        
                Connection * connection = map4[ip];

                if( connection == nullptr )
                {
                        DBG("ConMan::send() connection not found, new connection")
                        connection = new Connection( ip );
                }

        map4Mutex.unlock();

        {
                std::unique_lock<std::mutex> lock( connGuardsMutex );
                connectionGuards[ ip ].lock();  
        }

        connection->send(msg);

        if( connection->getCounter() > 3 )
        {
                delete connection;
                connection = nullptr;
        }

        std::unique_lock<std::mutex> lock( connGuardsMutex );
        connectionGuards[ ip ].unlock();
}

void ConnectionManager::receive( const Ipv4 & ip, message::Message * const msg )
{
        DBG("ConMan::receive( " << ip.getAddress() << " )")
        
        Connection * connection;
       
        {
                std::unique_lock<std::mutex> lock(map4Mutex);

                connection  = map4[ip];

                if( connection == nullptr )
                {
                        DBG("ConMan::rec() connection not found, waiting for new connection")
                        
                        std::condition_variable & conVar = receiveGuards[ip];

                        conVar.wait(lock);                        
                }
        }

        connGuardsMutex.lock();
        connectionGuards[ ip ].lock();  
        connGuardsMutex.unlock();

        connection->receive(msg);

        if( connection->getCounter() > 3 )
        {
                delete connection;
                connection = nullptr;
        }

        connGuardsMutex.lock();
        connectionGuards[ ip ].unlock();
        connGuardsMutex.unlock();
}

void ConnectionManager::remove( const Ipv4 & ip )
{
        DBG("ConMan::remove( " << ip.getAddress() << " )")

        map4Mutex.lock();

                try
                {
                        Connection * connection = map4.at( ip );

                        connGuardsMutex.lock();
                        connectionGuards[ ip ].lock();  
                        connGuardsMutex.unlock();
                        
                        if( connection != nullptr )
                                delete connection;
        
                        connGuardsMutex.lock();
                        connectionGuards[ ip ].unlock();
                        connGuardsMutex.unlock();

                        map4.erase( ip );
                }
                catch ( std::out_of_range e )
                {
                        // nic, nie ma elementu do usunięcia
                }

        map4Mutex.unlock();

        connGuardsMutex.lock();
                connectionGuards.erase(ip);
        connGuardsMutex.unlock();
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
