/** \file console.cpp
 * \author Kacper Stachyra
 * \brief Glowny plik konsoli administratora, watek klienta; uruchamia klient i serwer dla komunikatów.
 */

#include "ConsoleServer.hpp"
#include "ConsoleClient.hpp"

using namespace std;

int main(int argi, char* argv[])
{
    ConsoleClient *consoleClient = new ConsoleClient();

    consoleClient->start();

    delete consoleClient;

    return 0;
}
