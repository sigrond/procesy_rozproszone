/** \file console.cpp
 * \author Kacper Stachyra
 * \brief Glowny plik konsoli administratora, watek klienta; uruchamia klient i serwer dla komunikatów.
 */

//#include <thread>

#include "ConsoleServer.hpp"
#include "ConsoleClient.hpp"

using namespace std;

int main(int argi, char* argv[])
{
    ConsoleServer *consoleServer = new ConsoleServer();
    ConsoleClient *consoleClient = new ConsoleClient();

    //thread serverThread(consoleServer->run())

    consoleClient->start();

    delete consoleClient;
    delete consoleServer;

    return 0;
}
