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
        Controller* controller=new Controller();/**< kontroler jest sercem serwera, o architekturze zbliżonej do modelu MVC */
        controller->setAdminServer(new AdminServer());/** AdminServer i AgentServer można traktować jak swego rodzaju widoki MVC */
        controller->setAgentServer(new AgentServer());
        controller->setModel(new Model());
        controller->setup();
        thread controllerThread(&Controller::start,controller);
        /** \todo wymyslić jakieś zgrabne zamknięcie oczekiwania na opcjonalne polecenia,
         * albo zrezygnować z takiej możliwości.
         */
        string s;
        while(cin>>s)
        {
            if(s.compare("exit")==0)
            {
                /** \todo wstawić jakiś zgrabny przełącznik do kończenia wątka kontrolera */
                break;
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
