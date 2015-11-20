/** \file server.cpp
 * \author Tomasz Jakubczyk
 * \brief Głowny plik serwera zarządzającego procesami rozproszonymi.
 *
 */

 #include "Controller.h"
 #include "AdminServer.h"
 #include "AgentServer.h"

int main(int argi, char* argv[])
{
    Controller controller=new Controller();
    controller->setAdminServer(new AdminServer());
    controller->setAgentServer(new AgentServer());
    controller->start();
    delete controller;
    return 0;
}
