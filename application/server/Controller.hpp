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
    /** \brief w tej metodzie wszystko się dzieje, w szczególności wywołuje ona nowe wątki
     * \return void
     * \throw ControllerException
     */
    void start();
    void triggerShutDown();
    int alive;
    /** \brief Tworzy kolejkę blokującą i podaje wskazanie na nią do serverów i modelu.
     * Odzieliłem tą metodę od start(), bo występował wyścig i czasem wątki chciały wrzucać zdarzeńa do kolejki zanim kolejka powstała.
     * \return void
     * \throw ControllerException
     */
    void setup();
private:
	friend class AddAgentStrategy;
    AdminServer* adminServer;
    AgentServer* agentServer;
    Model* model;
    BlockingQueue<Event*>* blockingQueue;/**< kolejka blokująca na której pojawiają się zdarzenia do obsłużenia */
    std::map<EventType,Strategy*>* strategyMap;/**< mapa strategii pozwalająca zdecydować jak obsłużyć dany typ zdarzenia */
    /** \brief metoda wypełnia mapę strategii odpowiednimi strategiami dla różnych typów zdarzeń
     * \return void
     * \throw ControllerException
     */
    void fillStrategyMap();
    bool shutDownServer;
};
