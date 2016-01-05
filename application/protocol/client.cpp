#include "ConnectionManager.hpp"

#include <string>
using namespace message;
#include <thread>
#include <iostream>
#include <cstdlib>

void communication ( ConnectionManager * cm, Ipv4 * ip, unsigned port)
{
	Message * msg1 = nullptr;

	std::vector<unsigned long> v (3);
	v[0] = 666;
	v[1] = 42;
	v[2] = 88;

        Message * msg2 = new depMessage( State::REQ, v );
        Message * msg3 = new depMessage( State::ACK );

	cm->send( *ip, *msg2, port + 55555 );

	msg2->print();

	cm->receive( *ip, msg1, port + 55555 );

	if( msg1 )
		msg1->print();

	cm->receive( *ip, msg1, port + 55555 );

	if( msg1 )
		msg1->print();

	cm->send( *ip, *msg3, port + 55555 );

	msg3->print();

}

int main( int argc, char** argv)
{

        if(argc > 1)
        {
			#ifdef __CYGWIN__
        	unsigned n = strtol(argv[1],0,10);
        	#else
			unsigned n = std::stoi( std::string( argv[1] ));
        	#endif // __CYGWIN__

                ConnectionManager * mietek = ConnectionManager::getInstance( 55555 + n );

                Ipv4 ip = Ipv4("127.0.0.1");

		getchar();

		std::thread * tq;

		std::thread t (communication, mietek, &ip, 0 );

                getchar();

		t.join();
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
