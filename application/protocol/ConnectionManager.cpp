/** 
 * \file ConnectioniManager.cpp
 *
 * \brief  Plik z implementacjami metod klasy ConnectionManager
 *
 * \author Andrzej Roguski
 */

#include "ConnectionManager.hpp"

// tak, to działa i jest bezpieczne wątkowo (Magic Statics)
// C++11 takie piękne
ConnectionManager & ConnectionManager::getInstance()
{
        static ConnectionManager instance;
        return instance;  
}

void ConnectionManager::send( const Ip & ip, const message::Message & msg )
{

}

void ConnectionManager::receive( const Ip & ip, message::Message * const msg )
{

}
