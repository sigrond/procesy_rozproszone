/** \file server.cpp
 * \author Tomasz Jakubczyk
 * \brief Głowny plik serwera zarządzającego procesami rozproszonymi.
 * \date
 * Low Orbit Task Cannon
 */

#include "Controller.hpp"
#include "AdminServer.hpp"
#include "AgentServer.hpp"
#include "Model.hpp"
#include "Strategies.hpp"
#include "version.h"

#include <thread>
#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>

using namespace std;

int TestStrategy::createdObjects=0;
int TestStrategy::deletedObjects=0;

int main(int argi, char* argv[])
{
    try
    {
    	if(argi>1)
		{
			for(int i=1;i<argi;i++)
			{
				string sc(argv[i]);
				if(sc.find("-h")!=string::npos)
				{
					cout<<"Serwer LOTC help"<<endl;
					cout<<"Argumenty uruchamiania:"<<endl;
					cout<<"-h wyświetla pomoc"<<endl;
					cout<<"Jeśli jako pierwszy argument podany jest adres IP, to jest to adres zdalnej konsoli administra. w przeciwnym przypadku konsola administratora powinna być na 127.0.0.1"<<endl<<endl;
					cout<<"Podczas pracy serwera obsługiwane są następujące polecenia:"<<endl;
					cout<<"add agent wymagany_adres_ip opcjonalny_numer portu	-	dodanie adresu agenta"<<endl;
					cout<<"add task nazwa_pliku_lub_polecenia	-	zlecenie zadania"<<endl;
					cout<<"exit	-	polecenie zamykania serwera, przynajmniej próbujemy zrobić to po dobroci, choć szanse są marne"<<endl<<endl;
					return 0;
				}
			}
		}
        cout<<"Witamy w serwerze LOTC!"<<endl;
        cout<<"build:"<<endl;
        cout<<AutoVersion::FULLVERSION_STRING<<endl;
        Controller* controller=new Controller();/**< kontroler jest sercem serwera, o architekturze zbliżonej do modelu MVC */
        //controller->setAdminServer(new AdminServer());/** AdminServer i AgentServer można traktować jak swego rodzaju widoki MVC */
        Ipv4* adminIP=nullptr;
        if(argi>1)
		{
			adminIP=new Ipv4(string(argv[1]));
		}
		else
		{
			adminIP=new Ipv4("127.0.0.1");
		}
        controller->setAdminServer(new AdminServer(*static_cast<Ip*>(adminIP)));
        controller->setAgentServer(new AgentServer());
        Model* model=new Model();
        controller->setModel(model);
        controller->setup();
        thread controllerThread(&Controller::start,controller);
        /** \todo wymyslić jakieś zgrabne zamknięcie oczekiwania na opcjonalne polecenia,
         * albo zrezygnować z takiej możliwości.
         */
        string s;
        string ss;
        while(getline(cin,s))
        {
            if(s.compare("exit")==0)
            {
            	cout<<"Polecenie exit bezpośrednio do serwera"<<endl;
            	controller->triggerShutDown();
                /** \todo wstawić jakiś zgrabny przełącznik do kończenia wątka kontrolera */
                break;
            }
            else if(s.find("add")==0)
			{
				cout<<s<<endl;
				unsigned int i=s.find("agent");
				cout<<i<<endl;
				if(i!=string::npos && s.size()>10)
				{
					ss=s.substr(10);
					cout<<ss<<endl;
					unsigned int j=ss.find(" ");
					if(j!=string::npos)
					{
						string iP=ss.substr(0,j);
						Ipv4* ip=new Ipv4(iP);
						string port=ss.substr(j);
						cout<<"Dodawanie agenta: "<<ip->getAddress()<<endl;
						int portt=strtol(port.c_str(),nullptr,10);
						cout<<"port agenta: "<<portt<<endl;
						model->pushAddAgent(ip,portt);
					}
					else
					{
						Ipv4* ip=new Ipv4(ss);/**< dalej opiekunem tego adresu zostaje slave i nikt inny nie powinnien wywołać destruktora */
						/**< \todo sprawdzanie poprawności adresu */
						cout<<"Dodawanie agenta: "<<ip->getAddress()<<endl;
						model->pushAddAgent(ip,46000);
					}
					continue;
				}
				i=s.find("task");
				cout<<i<<endl;
				if(i!=string::npos && s.size()>9)
				{
					ss=s.substr(9);
					cout<<ss<<endl;
					cout<<"Dodawanie zadania: "<<ss<<endl;
					model->addTask(ss);
					continue;
				}
			}
        }
        if(controllerThread.joinable())
		{
            controllerThread.join();
		}
        //delete controllerThread;
        delete controller;
    }
    catch(exception &e)
    {
        cerr<<e.what()<<endl;
    }
    catch(...)
    {
        cerr<<"nieznany wyjątek"<<endl;
    }
    return 0;
}
