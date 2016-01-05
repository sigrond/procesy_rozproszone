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

		unsigned short port = conMan->listeningSocket->getPort();
                
                DBG("accepted " << conMan->listeningSocket->getIp().getAddress() << ":" << port )
                
                conMan->map4Mutex.lock();

			AddressIpv4 addr = AddressIpv4( ip, port + 10000 );
		
			Connection ** connection;	

			if( conMan->listeningPort == SERVER_PORT )
				connection = &conMan->map4[ addr ];
			else
				connection = &conMan->map4[ conMan -> lockAddr ];

                        if( *connection == nullptr )
                        {
                                DBG("awaitConnections(): connection not found, new connection")
                                *connection = new Connection( socket );

                                try
                                {
					std::condition_variable * conVar;

					if( conMan->listeningPort == SERVER_PORT )
						conVar = & conMan->receiveGuards.at( addr );
					else
						conVar = & conMan->receiveGuards.at( conMan -> lockAddr );

                                        conVar->notify_one();

					if( conMan->listeningPort == SERVER_PORT )
						conMan->receiveGuards.erase( addr );
					else
						conMan->receiveGuards.erase( conMan -> lockAddr );

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
ConnectionManager * ConnectionManager::getInstance( unsigned short listenPort )
{
        static ConnectionManager instance = ConnectionManager( listenPort );
        return &instance;  
}

ConnectionManager::ConnectionManager( unsigned short listenPort ) : listeningPort(listenPort), lockAddr( AddressIpv4(Ipv4(), 0) )
{
        DBG("ConnectionManager( " << listenPort << " )")
        listeningSocket = new SocketIp4( Ipv4(), listenPort );

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

void ConnectionManager::send( const Ipv4 & ip, const message::Message & msg, unsigned short port )
{
        DBG("ConMan::send( " << ip.getAddress() << ", " << port << " )")

        map4Mutex.lock();
		AddressIpv4 addr = AddressIpv4( ip, port );

                Connection * & connection = map4[ addr ];

                if( connection == nullptr )
                {
                        DBG("ConMan::send() connection not found, new connection")
                        connection = new Connection( ip, port, listeningPort - 10000 );
                }

        map4Mutex.unlock();

        {
                std::unique_lock<std::mutex> lock( connGuardsMutex );
                connectionGuards[ addr ].lock();  
        }

        connection->send(msg);

        if( connection->getCounter() > 3 )
        {
                delete connection;
                connection = nullptr;
        }

        std::unique_lock<std::mutex> lock( connGuardsMutex );
        connectionGuards[ addr ].unlock();
}

void ConnectionManager::receive( const Ipv4 & ip, message::Message * & msg, unsigned short port )
{
        DBG("ConMan::receive( " << ip.getAddress() << ", " << port << " )")
        
        std::unique_lock<std::mutex> lock(map4Mutex);

		AddressIpv4 addr = AddressIpv4( ip, port );

                Connection * & connection = map4[ addr ];

                if( connection == nullptr )
                {
                        DBG("ConMan::rec() connection not found, waiting for new connection")
                       
			lockAddr = addr;

                        std::condition_variable & conVar = receiveGuards[ addr ];

                        conVar.wait(lock);

                        connection = map4[ addr ];
                }

        lock.unlock(); 

        connGuardsMutex.lock();
        connectionGuards[ addr ].lock();  
        connGuardsMutex.unlock();

        connection->receive(msg);

        if( connection->getCounter() > 3 )
        {
                delete connection;
                connection = nullptr;
        }

        connGuardsMutex.lock();
        connectionGuards[ addr ].unlock();
        connGuardsMutex.unlock();
}

void ConnectionManager::remove( const Ipv4 & ip, unsigned short port )
{
        DBG("ConMan::remove( " << ip.getAddress() << ", " << port << " )")

        map4Mutex.lock();
	
		AddressIpv4 addr = AddressIpv4( ip, port );
                
		try
                {
                        Connection * connection = map4.at( addr );

                        connGuardsMutex.lock();
                        connectionGuards[ addr ].lock();  
                        connGuardsMutex.unlock();
                        
                        if( connection != nullptr )
                                delete connection;
        
                        connGuardsMutex.lock();
                        connectionGuards[ addr ].unlock();
                        connGuardsMutex.unlock();

                        map4.erase( addr );
                }
                catch ( std::out_of_range e )
                {
                        // nic, nie ma elementu do usunięcia
                }

        map4Mutex.unlock();

        connGuardsMutex.lock();
                connectionGuards.erase( addr );
        connGuardsMutex.unlock();
}

void ConnectionManager::send( const Ipv6 & ip, const message::Message & msg, unsigned short port )
{

}

void ConnectionManager::receive( const Ipv6 & ip, message::Message * & msg, unsigned short port )
{

}

void ConnectionManager::remove( const Ipv6 & ip, unsigned short port )
{

}
