/** \file Agent.cpp
 * \author Eryk Raty�ski
 * \brief Plik g��wny dla agenta
 */

#include "AgentClient.hpp"

//#include <thread>
#include <iostream>
#include <string>

using namespace std;

int main(int argi, char* argv[])
{
	AgentClient* agentClient = new AgentClient();
	//thread clientThread(agentClient->start());

	string s;
	while(cin >> s)
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

