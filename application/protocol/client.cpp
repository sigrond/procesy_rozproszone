#include "ConnectionManager.hpp"

#include <string>
using namespace message;
#include <thread>
#include <iostream>
#include <cstdlib>

void rec ( ConnectionManager * cm, Ipv4 * ip, unsigned port)
{
	Message * msg1 = nullptr;

        
	std::string fname = "./testfile";

	Message * msg2 = new fileMessage( State::REQ, true, 3, fname );
        Message * msg3 = new fileMessage( State::ACK );

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

void send_ ( ConnectionManager * cm, Ipv4 * ip, unsigned port)
{
	std::vector<Ipv4> v (4);

	v[0] = Ipv4( "1.1.1.1" );
	v[1] = Ipv4( "2.2.2.2" );
	v[2] = Ipv4( "3.3.3.3" );
	v[3] = Ipv4( "4.4.4.4" );

        Message * msg2 = new hostMessage( HostSub::H_RM, State::REQ, v );
        Message * msg3 = new hostMessage( State::ACK );

	cm->send( *ip, *msg2, port + 55555 );

	msg2->print();

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

		//std::thread t_ (send_, mietek, &ip, 0 );

		//getchar();
		std::thread t (rec, mietek, &ip, 0 );

                getchar();

		t.join();
		//t_.join();
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
