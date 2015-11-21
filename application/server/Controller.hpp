/** \file Controller.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy kontrolera
 *
 */

#pragma once

#include "AdminServer.hpp"
#include "AgentServer.hpp"
#include "Model.hpp"
#include "BlockingQueue.hpp"

/** \brief klasa kontrolera
 */
class Controller
{
public:
    Controller();
    ~Controller();
    void setAdminServer(AdminServer*);
    void setAgentServer(AgentServer*);
    void setModel(Model*);
    void start();/**< w tej metodzie wszystko się dzieje, w szczególności wywołuje ona nowe wątki */
private:
    AdminServer* adminServer;
    AgentServer* agentServer;
    BlockingQueue* blockingQueue;
};
