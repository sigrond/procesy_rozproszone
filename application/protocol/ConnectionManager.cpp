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

                Connection ** connection = &(conMan->map4[ip]);

                if( *connection == nullptr )
                {
                        DBG("awaitConnections(): connection not found, new connection")
                        *connection = new Connection( socket );
                }
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
        Connection ** connection = &map4[ip];

        if( *connection == nullptr )
        {
                DBG("ConMan::send() connection not found, new connection")
                *connection = new Connection( ip );
        }
        
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
        Connection ** connection = &map4[ip];

        if( *connection == nullptr )
        {
                DBG("ConMan::rec() connection not found, new connection")
                *connection = new Connection( ip );
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
