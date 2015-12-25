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
                
                conMan->mapMutex.lock();

                        Connection ** connection = &(conMan->map4[ip]);

                        if( *connection == nullptr )
                        {
                                DBG("awaitConnections(): connection not found, new connection")
                                *connection = new Connection( socket );

                                try
                                {
                                        std::condition_variable * conVar = conMan->map4Guards.at( ip );

                                        conVar->notify_one();
                                }
                                catch( std::out_of_range e)
                                {
                                        // nic, po protu nikt nie czeka na wiadomość z adresu IP == ip
                                }
                        }

                conMan->mapMutex.unlock();
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

        mapMutex.lock();
        
                Connection ** connection = &map4[ip];

                if( *connection == nullptr )
                {
                        DBG("ConMan::send() connection not found, new connection")
                        *connection = new Connection( ip );
                }

        mapMutex.unlock();
        
        (*connection)->send(msg);

        if( (*connection)->getCounter() == 4 )
        {
                delete (*connection);
                *connection = nullptr;
        }
}

void ConnectionManager::receive( const Ipv4 & ip, message::Message * const msg )
{
        DBG("ConMan::receive( " << ip.getAddress() << " )")
        
        Connection ** connection;
       
        {
                std::unique_lock<std::mutex> lock(mapMutex);

                connection  = &map4[ip];

                if( *connection == nullptr )
                {
                        DBG("ConMan::rec() connection not found, waiting for new connection")
                        
                        std::condition_variable ** conVar = &map4Guards[ip];
                        
                        *conVar = new std::condition_variable();

                        (*conVar)->wait(lock);                        
                }
        }

        (*connection)->receive(msg);

        if( (*connection)->getCounter() == 4 )
        {
                delete (*connection);
                *connection = nullptr;
        }

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
