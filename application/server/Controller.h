/** \file Controller.h
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy kontrolera
 *
 */

 #pragma once

 #include "AdminServer.h"
 #include "AgentServer.h"

/** \brief klasa kontrolera
 */
class Controller
{
public:
    Controller();
    ~Controller();
    void setAdminServer(AdminServer*);
    void setAgentServer(AgentServer*);
    void start();/**< w tej metodzie wszystko się dzieje, w szczególności wywołuje ona nowe wątki */
private:
    AdminServer* adminServer;
    AgentServer* agentServer;
};
