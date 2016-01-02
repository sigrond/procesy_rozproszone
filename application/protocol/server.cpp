#include "ConnectionManager.hpp"

#include <string>
using namespace message;
#include <thread>
#include <iostream>

void communication ( ConnectionManager * cm, Ipv4 * ip, Message * msg1, Message * msg2)
{	
	cm->receive( *ip, msg1 );

	cm->send( *ip, *msg2 );

	cm->receive( *ip, msg1 );

	cm->send( *ip, *msg2 );

}

int main( int argc, char** argv)
{

        if(argc > 1)
        {
                ConnectionManager * mietek = ConnectionManager::getInstance();
                Message * msg1 = nullptr;

                Message * msg2 = new pingMessage( State::REQ );

                Ipv4 ip = Ipv4( std::string(argv[1]) );

		Ipv4 ocDonutSteal = Ipv4("1.2.3.4");
		Ipv4 copy = Ipv4( ocDonutSteal );

		std::cout << "1.2.3.4? " << ocDonutSteal.getAddress() << std::endl;
		std::cout << "1.2.3.4? " << copy.getAddress() << std::endl;

		Ipv4 change = Ipv4("5.6.7.8");
		ocDonutSteal = change;
		change = copy;

		std::cout << "5.6.7.8? " << ocDonutSteal.getAddress() << std::endl;
		std::cout << "1.2.3.4? " << change.getAddress() << std::endl;
	
		getchar();

		Ipv4 ip1 = Ipv4("10.10.10.10");
		Ipv4 ip2 = Ipv4("10.10.10.11");
		Ipv4 ip3 = Ipv4("10.10.10.12");
		Ipv4 ip4 = Ipv4("10.10.10.13");
		Ipv4 ip5 = Ipv4("10.10.10.14");

		std::thread t1 (communication, mietek, &ip1, msg1, msg2);
		std::thread t2 (communication, mietek, &ip2, msg1, msg2);
		std::thread t3 (communication, mietek, &ip3, msg1, msg2);
		std::thread t4 (communication, mietek, &ip4, msg1, msg2);
		std::thread t5 (communication, mietek, &ip5, msg1, msg2);

                getchar();

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
