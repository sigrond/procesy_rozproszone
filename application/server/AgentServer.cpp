/** \file AgentServer.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami metod klasy serwera klienta / agenta
 *
 */

#include "AgentServer.hpp"
#include <exception>
#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;

/** \brief Klasa opakowująca exception dla AgentServer
 */
struct AgentServerException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	AgentServerException(std::string s)
	{
		m="AgentServerException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

AgentServer::AgentServer() :
	blockingQueue(nullptr),
	slaves(nullptr),
	shutDown(false),
	connectionManager(nullptr)
{
	#ifdef _DEBUG
	cout<<"AgentServer::AgentServer()"<<endl;
	#endif // _DEBUG
	connectionManager=ConnectionManager::getInstance();
	slaves=new std::vector<Slave*>();
}

AgentServer::~AgentServer()
{
	if(slaves!=nullptr)
	{
		for(unsigned int i=0;i<slaves->size();i++)
		{
			if(slaves->at(i)!=nullptr)
			{
				delete slaves->at(i);
				slaves->at(i)=nullptr;/** przezorny zawsze ubezpieczony :D
										* BTW na pewno gdzieś w okolicach tego regionu
										* kodu będą problemy. więc:
										* \todo testy jednostkowe! :) */
			}
		}
		delete slaves;
		slaves=nullptr;
	}
	if(blockingQueue!=nullptr)
	{
		delete blockingQueue;
		blockingQueue=nullptr;
	}
/*	if(connectionManager!=nullptr)
	{
		delete connectionManager;
		connectionManager=nullptr;
	}*/
}

void AgentServer::connect(Slave* who, message::Message* m)
{
	connectionManager->send(*static_cast<Ipv4*>(who->getSlaveIP()),*m);/**< \todo dodać jakiś zabezpieczeń bo groźnie to wygląda */
}

void AgentServer::listen(Slave* who)
{
	#ifdef _DEBUG
	cout<<"AgentServer::listen(Slave* who)"<<endl;
	#endif // _DEBUG
	message::Message* m=nullptr;
	//m=who->getConnection()->receive();
	while(!shutDown)
	{
		connectionManager->receive(*static_cast<Ipv4*>(who->getSlaveIP()),m);
		#ifdef _DEBUG
		cout<<"AgentServer::listen odebrano: "<<m<<endl;
		#endif // _DEBUG
		blockingQueue->push_back(new Event(MESSAGE_FROM_AGENT_SERVER,m));
	}
	who->setListening(false);
}

void AgentServer::setBlockingQueue(BlockingQueue<Event*>* q)
{
	blockingQueue=q;
}

/** \brief dodajemy ip agenta do wektora slaves i dajemy znać jeśli jakiś wątek czekał na to
 *
 * \param ip Ip&
 * \return void
 *
 */
void AgentServer::addSlave(Ip &ip)
{
	#ifdef _DEBUG
	cout<<"AgentServer::addSlave(Ip &ip)"<<endl;
	#endif // _DEBUG
	if(slaves==nullptr)
	{
		throw AgentServerException("slaves==nullptr");
	}
	slavesMutex.lock();
	slaves->push_back(new Slave(ip));
	slavesMutex.unlock();
	unique_lock<mutex> allListeningMutexLock(allListeningMutex);
	allListeningMutexLock.unlock();
	allListeningCondition.notify_one();//zgłaszamy, że już nie wszystkie agenty słuchają

	unique_lock<mutex> waitForTaskMutexLock(waitForTaskMutex);
    waitForTaskMutexLock.unlock();
    waitForTaskCondition.notify_one();//zgłaszamy, że może można przydzielić zadanie
}

/** \brief teraz zrezygnowałem z wykożystania tej funkcji na rzecz AgentServer::start()
 *
 * \return void
 *
 */
void AgentServer::listenToAll()/**< \todo dobrze przemyśleć jak ma działać */
{
	//std::thread* t;/**< \todo ? wątki tutaj potrzebne? */
	for(unsigned int i=0;i<slaves->size();i++)
	{
		listen(slaves->at(i));/**< \todo jakiś if, bo jak się doda nowy to co */
	}
}

void AgentServer::start()
{
	shutDown=false;
	#ifdef _DEBUG
	cout<<"AgentServer::start()"<<endl;
	#endif // _DEBUG
	//chcemy słuchać na wszystkie agenty w osobnych wątkach
	thread* t=nullptr;
    slavesMutex.lock();
    for(unsigned int i=0;i<slaves->size();i++)
	{
		slaves->at(i)->setListening(true);
		t=new thread(&AgentServer::listen,this,slaves->at(i));
		slaves->at(i)->slaveThread=t;
	}
	slavesMutex.unlock();

	thread distributeTasksThread(&AgentServer::distributeTasks,this);

	//jeśli pojawi się nie słuchający agent, to niech słucha
	unsigned int i=0;
	bool allListening=false;
	bool listenSlave=false;
	while(!shutDown)//pętla zlecania zadań nasłuchiwania
	{
		#ifdef _DEBUG
		cout<<"pętla nasłuchiwania agentów i: "<<i<<"listen slave: "<<listenSlave<<endl;
		#endif // _DEBUG
		slavesMutex.lock();
		if(slaves->empty())
		{
			unique_lock<mutex> allListeningMutexLock(allListeningMutex);
			while(slaves->empty())
			{
				#ifdef _DEBUG
				cout<<"slaves->empty()"<<endl;
				#endif // _DEBUG
				slavesMutex.unlock();
				allListeningCondition.wait(allListeningMutexLock);
				slavesMutex.lock();
			}
		}
		if(i>=slaves->size())
		{
			i=0;
			if(listenSlave)
			{
				allListening=false;
			}
			else
			{
				allListening=true;
			}
			listenSlave=false;
			if(allListening)
			{
				#ifdef _DEBUG
				cout<<"allListeningCondition.wait(allListeningMutexLock)"<<endl;
				#endif // _DEBUG
				slavesMutex.unlock();
				unique_lock<mutex> allListeningMutexLock(allListeningMutex);
				allListeningCondition.wait(allListeningMutexLock);//niech sobie torchę zaczeka, aż pojawi sie nie słuchający agent
				#ifdef _DEBUG
				cout<<"koniec allListeningCondition.wait"<<endl;
				#endif // _DEBUG
				i=0;
				continue;
				slavesMutex.lock();
			}
		}
		slavesMutex.unlock();
        if(!slaves->at(i)->getListening())
		{
			listenSlave=true;
			slaves->at(i)->setListening(true);
			t=new thread(&AgentServer::listen,this,slaves->at(i));
			slaves->at(i)->slaveThread=t;
			#ifdef _DEBUG
			cout<<"dodany wątek agenta IP: "<<slaves->at(i)->getSlaveIP()->getAddress()<<endl;
			#endif // _DEBUG
		}
		i++;
	}
}

void AgentServer::triggerShutDown()
{
	shutDown=true;
	slavesMutex.lock();
	for(unsigned int i=0;i<slaves->size();i++)
	{
		slavesMutex.unlock();
		#ifdef _DEBUG
		cout<<"próbuję usunąć agenta: "<<slaves->at(i)->getSlaveIP()->getAddress()<< "z ConnectionManager..."<<endl;
		#endif // _DEBUG
		connectionManager->remove(*(Ipv4*)slaves->at(i)->getSlaveIP());
		#ifdef _DEBUG
		cout<<"udało się usunąć agenta: "<<slaves->at(i)->getSlaveIP()->getAddress()<< "z ConnectionManager!"<<endl;
		#endif // _DEBUG
		slavesMutex.lock();
	}
	slavesMutex.unlock();
}

void AgentServer::sendToAll(message::Message* m)
{
    slavesMutex.lock();
    for(unsigned int i=0;i<slaves->size();i++)
	{
		connect(slaves->at(i),m);
	}
    slavesMutex.unlock();
}

void AgentServer::addTask(Task* task)
{
    #ifdef _DEBUG
    cout<<"AgentServer::addTask(Task* task)"<<endl;
    #endif // _DEBUG
    unique_lock<mutex> waitForTaskMutexLock(waitForTaskMutex);
    tasks.insert(task);
    waitForTaskMutexLock.unlock();
    waitForTaskCondition.notify_one();
    #ifdef _DEBUG
    cout<<"waitForTaskCondition.notify_one()"<<endl;
    #endif // _DEBUG
}

bool AgentServer::cmp::operator()(Task* a, Task* b)
{
	return a->when<b->when;
}

void AgentServer::distributeTasks()
{
	unique_lock<mutex> waitForTaskMutexLock(waitForTaskMutex);
	std::multiset<Task*,cmp>::iterator it;
	while(!shutDown)
	{
		while(tasks.empty())
		{
			#ifdef _DEBUG
			cout<<"czekam na zadanie..."<<endl;
			#endif // _DEBUG
			waitForTaskCondition.wait(waitForTaskMutexLock);
			#ifdef _DEBUG
			cout<<"pojawiło się zadanie..."<<endl;
			#endif // _DEBUG
		}
		slavesMutex.lock();
		it=tasks.begin();
		for(unsigned int i=0;i<slaves->size();i++)
		{
			slavesMutex.unlock();
			#ifdef _DEBUG
			cout<<"próbuję rozdysponować zadania do agentów i: "<<i<<" ..."<<endl;
			#endif // _DEBUG
            if(slaves->at(i)->ready)
			{
				if(it==tasks.end())
				{
					it=tasks.begin();
				}
				//usuwam zadania wykonane
				while(!tasks.empty() && it!=tasks.end() && (*it)->done)
				{
					tasks.erase(it);
					it=tasks.begin();
				}
				if(tasks.empty())
				{
					break;
				}
				//pomijam zadania wykonywane, dopóki ich los nie zostanie jakoś rozstrzygnięty
				/**< \todo potrzebny mechanizm do stwierdzania, czy nie trzeba uznać, że zadanie się nie wykona tak jak to było zlecone i trzeba je zlecić innemu agentowi */
				while(!tasks.empty() && it!=tasks.end() && (*it)->underExecution)
				{
					it++;
				}
				slaves->at(i)->setTask(*it);
				(*it)->underExecution=true;
				message::Message* m=new message::fileMessage(message::State::REQ,true,(*it)->taskID,(*it)->name,(*it)->file);
				connect(slaves->at(i),m);
				message::Message* m2=new message::taskMessage(message::TaskSub::T_ADD,message::State::REQ,true,1,(*it)->taskID,(*it)->when);
				connect(slaves->at(i),m2);
				it++;

			}
			slavesMutex.lock();
		}
		#ifdef _DEBUG
		cout<<"próba rozdzielenia zadań do agentów zakończona.."<<endl;
		#endif // _DEBUG
		slavesMutex.unlock();
		#ifdef _DEBUG
		cout<<"begin waitForTaskCondition.wait_for(waitForTaskMutexLock,chrono::seconds(5))"<<endl;
		#endif // _DEBUG
		waitForTaskCondition.wait_for(waitForTaskMutexLock,chrono::seconds(5));
		#ifdef _DEBUG
		cout<<"end waitForTaskCondition.wait_for(waitForTaskMutexLock,chrono::seconds(5))"<<endl;
		#endif // _DEBUG
	}

}





















