/** \file AgentServer.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy serwera klienta / agenta
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "Slave.hpp"
#include "../protocol/ConnectionManager.hpp"
#include <vector>
#include <mutex>
#include <condition_variable>

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
    void start();
private:
    BlockingQueue<Event*>* blockingQueue;
    std::vector<Slave*>* slaves;
    bool shutDown;
    ConnectionManager* connectionManager;
    std::mutex slavesMutex;/**< w niektórych momentach chciałbym wiedzieć ile mam agentów */
    std::mutex allListeningMutex;
    std::condition_variable allListeningCondition;
};
