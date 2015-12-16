/** \file AgentServer.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy serwera klienta / agenta
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "Slave.hpp"
#include "../protocol/Connection.hpp"
#include <vector>

/** \brief klasa serwera agenta
 */
class AgentServer
{
public:
    AgentServer();
    ~AgentServer();
    void listen(Slave* who);/**< metoda nasłuchująca na połączenie z agentów. może być zrealizowana przez fork-server */
    void connect(Slave* who, message::Message* m);/**< metoda łącząca się z agentem */
    void setBlockingQueue(BlockingQueue<Event*>*);
    void addSlave(Ip &ip);
    void listenToAll();
private:
    BlockingQueue<Event*>* blockingQueue;
    std::vector<Slave*>* slaves;
};
