#include "ConnectionManager.hpp"

#include <string>
#include <thread>
#include <iostream>

using namespace message;

int main( int argc, char** argv)
{

        if(argc > 1)
        {
                ConnectionManager * mietek = ConnectionManager::getInstance();
                Message * msg1 = nullptr;

                Message * msg2 = new pingMessage( State::REQ );

                Ipv4 ip = Ipv4( std::string(argv[1]) );

                getchar();


                // ISHYGDDT

                // rrraz
                std::thread ( [=] {mietek->receive( ip, msg1 ); } );
                
                std::thread ( [=] {mietek->send( ip, *msg2 ); } );

                std::thread ( [=] {mietek->receive( ip, msg1 ); } );

                std::thread ( [=] {mietek->send( ip, *msg2 ); } );

                // dwa
                std::thread ( [=] {mietek->receive( ip, msg1 ); } );
                
                std::thread ( [=] {mietek->send( ip, *msg2 ); } );

                std::thread ( [=] {mietek->receive( ip, msg1 ); } );

                std::thread ( [=] {mietek->send( ip, *msg2 ); } );

                // usuwamy
                std::thread ( [=] {mietek->remove( ip ); } );

                // rrraz
                std::thread ( [=] {mietek->receive( ip, msg1 ); } );
                
                std::thread ( [=] {mietek->send( ip, *msg2 ); } );

                std::thread ( [=] {mietek->receive( ip, msg1 ); } );
                
                std::thread ( [=] {mietek->send( ip, *msg2 ); } );
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
