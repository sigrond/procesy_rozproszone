#include "ConnectionManager.hpp"

#include <string>
using namespace message;
#include <thread>
#include <iostream>
#include <cstdlib>
#include <chrono>

#include "debug.h"

void communication ( ConnectionManager * cm, Ipv4 * ip, unsigned port )
{
	Message * msg1 = nullptr;

        Message * msg2 = new hostMessage( State::ACK );
        Message * msg3 = new hostMessage( State::OK );


	cm->receive( *ip, msg1, port + 55555 );

	if( msg1 )
	{
		msg1->print();
		std::vector<Ipv4> v = static_cast<message::hostMessage*>(msg1) -> getAddresses();

		for(Ipv4 i : v)
			DBG( "IP: " << i.getAddress() );
	}

	cm->send( *ip, *msg2, port + 55555 );

	msg2->print();

	cm->send( *ip, *msg3, port + 55555 );

	msg3->print();

	cm->receive( *ip, msg1, port + 55555 );

	if( msg1 )
		msg1->print();
}

int main( int argc, char** argv)
{
	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now();

	std::chrono::steady_clock::duration d = tp.time_since_epoch();

	unsigned long l = d.count();

	std::cout << l << std::endl;

        if(argc > 1)
        {
        	#ifdef __CYGWIN__
        	unsigned agents = strtol(argv[1],0,10);
        	#else
			unsigned agents = std::stoi( std::string( argv[1] ));
        	#endif // __CYGWIN__

                ConnectionManager * mietek = ConnectionManager::getInstance( 55555 );

                Ipv4 ip = Ipv4("127.0.0.1");

		std::thread * t[agents];

		for(unsigned i = 0; i < agents; ++i )
			t[i] = new std::thread (communication, mietek, &ip, i+1 );

                getchar();

		for(unsigned i = 0; i < agents; ++i )
		{
			t[i]->join();
			delete t[i];
		}
        }
        else
        {
                std::cout << "Brak argumentów, łączenie z domyślnym adresem, proszę czekać." << std::endl;

                for(int i = 0; i<30 ; i++)
                {
                        usleep(100*1000);
                        std::cout << '.';
                        std::cout.flush();
                }

                std::cout << std::endl << "Połączono." << std::endl;

                usleep(500*1000);

                std::cout << std::endl << "Witamy w Piekielnych Wymiarach." << std::endl;

                std::cout << "Wysysanie duszy w toku:" << std::endl;

                for(int i = 0; i<30 ; i++)
                {
                        usleep(100*1000);
                        std::cout << '+';
                        std::cout.flush();
                }

                std::cout << std::endl << "Gotowe." << std::endl << std::endl;

                std::cout << "Dziękujemy za współpracę, Pańska dusza została pomyślnie skonsumowana." << std::endl;
                std::cout << "To cię nauczy nie zapominać o argumentach, nędzny śmiertelniku." << std::endl;

        }

        return 0;
}
