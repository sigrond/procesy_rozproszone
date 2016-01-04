#include "ConnectionManager.hpp"

#include <string>
using namespace message;
#include <thread>
#include <iostream>

void communication ( ConnectionManager * cm, Ipv4 * ip, unsigned port)
{	 
	Message * msg1 = nullptr;

        Message * msg2 = new synMessage( State::REQ );
        Message * msg3 = new synMessage( State::ACK );

	cm->send( *ip, *msg2, port + 55555 );

	cm->receive( *ip, msg1, port + 55555 );
	
	cm->receive( *ip, msg1, port + 55555 );

	cm->send( *ip, *msg2, port + 55555 );

}

int main( int argc, char** argv)
{

        if(argc > 1)
        {
		unsigned n = std::stoi( std::string( argv[1] ));

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
