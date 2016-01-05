#include "ConnectionManager.hpp"

#include <string>
using namespace message;
#include <thread>
#include <iostream>

#include "debug.h"

void communication ( ConnectionManager * cm, Ipv4 * ip, unsigned port )
{
	Message * msg1 = nullptr;

        Message * msg2 = new synMessage( State::ACK );
        Message * msg3 = new synMessage( State::OK );


	cm->receive( *ip, msg1, port + 55555 );

	cm->send( *ip, *msg2, port + 55555 );

	cm->send( *ip, *msg2, port + 55555 );

	cm->receive( *ip, msg1, port + 55555 );
}

int main( int argc, char** argv)
{

	Ipv4 ipp = Ipv4("0.0.0.0");
	unsigned short p = 1000;

	AddressIpv4 a = AddressIpv4(ipp, p);
	AddressIpv4 b = AddressIpv4(ipp, p);

	std::cout << (a < b) << " " << (b < a) << std::endl;

        if(argc > 1)
        {
		unsigned agents = std::stoi( std::string( argv[1] ));

                ConnectionManager * mietek = ConnectionManager::getInstance( 55555 );

                Ipv4 ip = Ipv4("127.0.0.1");

		getchar();

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
