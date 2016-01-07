/** \file console.cpp
 * \authors Kacper Stachyra, Tomasz Jakubczyk
 * \brief Glowny plik konsoli administratora, watek klienta,
 * \date 9 Dec 2015
 * Low Orbit Task Cannon
 */


#include "ConsoleClient.hpp"

using namespace std;

bool demo=false;

int main(int argi, char* argv[])
{
	if(argi>1)
		{
			for(int i=1;i<argi;i++)
			{
				string sc(argv[i]);
				cout<<"opcja: "<<sc<<endl;
				if(sc.find("-demo")!=string::npos)
				{
					demo=true;
					cout<<"demo"<<endl;
				}
				if(sc.find("-h")!=string::npos)
				{
					cout<<"Konsola LOTC help"<<endl;
					cout<<"Argumenty uruchamiania:"<<endl;
					cout<<"-h wyświetla pomoc"<<endl;
					cout<<"-demo wykonuje demonstracyjne połączenie z 127.0.0.1"<<endl<<endl;
					cout<<"Podczas pracy konsoli obsługiwane są następujące polecenia:"<<endl;
					cout<<"connect adres_IP_servera	-	sprawdzenie połączenia z serwerem"<<endl;
					//cout<<"add task nazwa_pliku_lub_polecenia	-	zlecenie zadania"<<endl;
					cout<<"exit	-	polecenie zamykania konsoli"<<endl<<endl;
					return 0;
				}
			}
		}
    ConsoleClient *consoleClient = new ConsoleClient();

    consoleClient->start();

    delete consoleClient;

    return 0;
}
