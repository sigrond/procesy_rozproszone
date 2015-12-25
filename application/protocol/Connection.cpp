/** 
 * \file Connection.cpp
 *
 * \brief Plik z implementacjami metod klasy Connection.
 *
 * \authors Tomasz Jakubczyk, Andrzej Roguski
 */

// UWAGA!!!
// Poniższy kod został wyprodukowany na (bardzo) szybko, w celach uzyskania JAKIEGOKOLWIEK połączenia
// Planowo do wigilii przestanie to wyglądać jak program napisany przez absolwenta szkoły wyższej informatyki i zarządzania



#include "Connection.hpp"

// chwilowo
#include <cstring>
#include <iostream>


#define DBG(x) std::cout << x << std::endl;

Connection::Connection ( const Ipv4 & address ) : counter(0)
{
        DBG("Connection(ip)")       
        socket = new SocketIp4( address );

        try
        {
                socket->connect();
        }
        catch (std::exception & e)
        {
                std::cerr << e.what() << std::endl;
        }
}

Connection::Connection ( const Ipv6 & address ) : counter(0)
{

}

Connection::Connection ( int msgsock ) : counter(0)
{
        DBG("Connection(int)")
        socket = new SocketIp4( msgsock );
}

Connection::~Connection ()
{
        DBG("~Connection(): My ancestors are smiling at me, Imperials. Can you say the same?")
        delete socket;
}

// There be dragons:

void Connection::send ( const message::Message & message )
{
        char pasta[] =  "Gomenasai, my name is Ken-Sama.\n"
                        "I’m a 27 year old American Otaku (Anime fan for you gaijins). I draw Anime and Manga on my tablet, and spend my days perfecting my art and playing superior Japanese games. (Disgaea, Final Fantasy, Persona series)\n"
                        "I train with my Katana every day, this superior weapon can cut clean through steel because it is folded over a thousand times, and is vastly superior to any other weapon on earth. I earned my sword license two years ago, and I have been getting better every day.\n"
                        "I speak Japanese fluently, both Kanji and the Osaka dialect, and I write fluently as well. I know everything about Japanese history and their bushido code, which I follow 100%\n"
                        "When I get my Japanese visa, I am moving to Tokyo to attend a prestigious High School to learn more about their magnificent culture. I hope I can become an animator for Studio Ghibli or a game designer!\n"
                        "I own several kimonos, which I wear around town. I want to get used to wearing them before I move to Japan, so I can fit in easier. I bow to my elders and seniors and speak Japanese as often as I can, but rarely does anyone manage to respond.\n"
                        "Wish me luck in Japan!\n";

        std::cout << "Send: " << socket->send( pasta, sizeof( pasta ) / sizeof( pasta[0] ) ) << std::endl;

        if( ++counter == 4)
                std::cout << "Close: " << socket->close() << std::endl;
}

void Connection::receive ( message::Message * const message )
{
        char pasta[1500];

        memset( pasta, 0, sizeof( pasta ));
      
       std::cout << "Read: " << socket->recv( pasta, sizeof( pasta ) / sizeof( pasta[0] ) ) << std::endl;
       std::string pastaStr(pasta);
       std::cout << "Received delicious pasta:" << std::endl << std::endl << pastaStr << std::endl;

       if( ++counter == 4)
                std::cout << "Close: " << socket->close() << std::endl;
}

char Connection::getCounter() const
{
        return counter;
}
