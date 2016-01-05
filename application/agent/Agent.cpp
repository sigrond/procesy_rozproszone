/** \file Agent.cpp
 * \author Eryk Ratyński
 * \brief Plik główny dla agenta
 */

#include "AgentClient.hpp"
#include "../protocol/ConnectionManager.hpp"
#include "../protocol/Ip.hpp"

#include <thread>
#include <iostream>
#include <string>




int main(int argi, char* argv[])
{

	Ipv4 * serverIP;
    if(argi == 1)/**dokonczyc pobranie adresu*/
    {
        //serverIP = new Ipv4(std::string(argv[1]) );

    }
    else
    {
        //serverIP = new Ipv4("127.0.0.1");
    }


	AgentClient* agentClient = new AgentClient( *static_cast<Ip*>(serverIP));
	//thread clientThread(agentClient->start());

	std::string s;
	while(std::cin >> s)
	{
		if(s.compare("exit") == 0)
			break;
	}
	/*
	if(clientThread.joinable())
	{
        clientThread.join();
	}
    delete clientThread;
    deleteagentClient;
	*/
	return 0;

}



