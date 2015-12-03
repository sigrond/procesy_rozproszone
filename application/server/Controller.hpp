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
#include "Event.hpp"
#include "Strategy.hpp"
#include <map>
#include <string>

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
    BlockingQueue<Event*>* blockingQueue;/**< kolejka blokująca na której pojawiają się zdarzenia do obsłużenia */
    std::map<EventType,Strategy*>* strategyMap;/**< mapa strategii pozwalająca zdecydować jak obsłużyć dany typ zdarzenia */
    void fillStrategyMap();/**< metoda wypełnia mapę strategii odpowiednimi strategiami dla różnych typów zdarzeń */
};
