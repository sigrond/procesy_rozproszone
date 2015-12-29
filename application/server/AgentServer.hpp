/** \file AgentServer.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy serwera klienta / agenta
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"
#include "Slave.hpp"
#include "Task.hpp"
#include "../protocol/ConnectionManager.hpp"
#include <vector>
#include <mutex>
#include <condition_variable>
#include <set>

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
    void triggerShutDown();
    void sendToAll(message::Message* m);
    void addTask(Task* task);
private:
    BlockingQueue<Event*>* blockingQueue;
    std::vector<Slave*>* slaves;
    bool shutDown;
    ConnectionManager* connectionManager;
    std::mutex slavesMutex;/**< w niektórych momentach chciałbym wiedzieć ile mam agentów */
    std::mutex allListeningMutex;
    std::condition_variable allListeningCondition;
    struct cmp
    {
    	bool operator()(Task* a, Task* b);
    };/**< niestety szablony nie lubią się z wyrażeniami lambda */;
    std::multiset<Task*,cmp> tasks;
    void distributeTasks();/**< metoda rozdzielająca zadania */
    std::mutex waitForTaskMutex;
    std::condition_variable waitForTaskCondition;
};
