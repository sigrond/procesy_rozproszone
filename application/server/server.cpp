/** \file server.cpp
 * \author Tomasz Jakubczyk
 * \brief Głowny plik serwera zarządzającego procesami rozproszonymi.
 *
 */

#include "Controller.hpp"
#include "AdminServer.hpp"
#include "AgentServer.hpp"
#include "Model.hpp"
#include "Strategies.hpp"

#include <thread>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

int TestStrategy::createdObjects=0;
int TestStrategy::deletedObjects=0;

int main(int argi, char* argv[])
{
    try
    {
        cout<<"Witamy w serwerze LOTC!"<<endl;
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
					Ipv4 ip=Ipv4(ss);/**< \todo sprawdzanie poprawności adresu */
					cout<<"Dodawanie agenta: "<<ip.getAddress()<<endl;
					model->pushAddAgent(ip);
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
