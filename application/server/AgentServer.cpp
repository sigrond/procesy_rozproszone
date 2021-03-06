/** \file AgentServer.cpp
 * \author Tomasz Jakubczyk
 * \brief plik z implementacjami metod klasy serwera klienta / agenta
 * \date 9 grudnia 215
 * Low Orbit Task Cannon
 */

#include "AgentServer.hpp"
#include <exception>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>

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
	#ifdef _DEBUG
	cout<<"wysyłam do agenta na port: "<<who->port<<endl;
	#endif // _DEBUG
	bool s=true;
	while(s)
	{
		try
		{
			connectionManager->send(*static_cast<Ipv4*>(who->getSlaveIP()),*m,who->port);/**< \todo dodać jakiś zabezpieczeń bo groźnie to wygląda */
			#ifdef _DEBUG
			cout<<"wysłaliśmy coś do agenta"<<endl;
			#endif // _DEBUG
			s=false;
		}
		catch(...)
		{
			#ifdef _DEBUG
			cout<<"agent send exceptin"<<endl;
			#endif // _DEBUG
			std::this_thread::sleep_for (std::chrono::milliseconds(1000));
		}
	}
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
		#ifdef _DEBUG
		cout<<"nasłuchiwanie agenta IP: "<<((Ipv4*)who->getSlaveIP())->getAddress()<<endl;
		#endif // _DEBUG
		try
		{
			#ifdef _DEBUG
			cout<<"czekamy na agent recive"<<endl;
			#endif // _DEBUG
			connectionManager->receive(*static_cast<Ipv4*>(who->getSlaveIP()),m,who->port);
			#ifdef _DEBUG
			cout<<"agent recive zakończyło"<<endl;
			#endif // _DEBUG
		}
		catch(...)
		{
			#ifdef _DEBUG
			cout<<"agent recive TIMEOUT"<<endl;
			#endif // _DEBUG
			if(who->getTask()==nullptr)
			{
				who->ready=false;
			}
			else
			{
				/**< \todo sprawdzić, czemu był timeout */
				//who->getTask()->underExecution=false;
				//who->getTask()->done=false;
			}
			return;
		}
		#ifdef _DEBUG
		cout<<"AgentServer::listen odebrano: "<<m<<endl;
		#endif // _DEBUG
		blockingQueue->push_back(new Event(MESSAGE_FROM_AGENT_SERVER,m,who));
		//jeśli przyszło coś od agenta i nie wykonyuje on zadania, to można przydzielić mu zadanie
		if(who->getTask()==nullptr)
		{
			who->ready=true;
		}
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
void AgentServer::addSlave(Ip* ip, unsigned short portNo)
{
	#ifdef _DEBUG
	cout<<"AgentServer::addSlave(Ip* ip)"<<endl;
	#endif // _DEBUG
	if(slaves==nullptr)
	{
		throw AgentServerException("slaves==nullptr");
	}
	slavesMutex.lock();
	slaves->push_back(new Slave(ip, portNo));
	#ifdef _DEBUG
	cout<<"Dodany agent ip: "<<((Ipv4*)slaves->back()->getSlaveIP())->getAddress()<<endl;
	#endif // _DEBUG
	slavesMutex.unlock();
	unique_lock<mutex> allListeningMutexLock(allListeningMutex);
	allListeningMutexLock.unlock();
	allListeningCondition.notify_one();//zgłaszamy, że już nie wszystkie agenty słuchają

	unique_lock<mutex> waitForTaskMutexLock(waitForTaskMutex);
    waitForTaskMutexLock.unlock();
    waitForTaskCondition.notify_one();//zgłaszamy, że może można przydzielić zadanie
    #ifdef _DEBUG
    cout<<"koniec AgentServer::addSlave(Ip* ip)"<<endl;
    #endif // _DEBUG
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
	if(slaves==nullptr)
	{
		throw AgentServerException("slaves==nullptr");
	}
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
		#ifdef _DEBUG2
		cout<<"pętla nasłuchiwania agentów i: "<<i<<"listen slave: "<<listenSlave<<endl;
		#endif // _DEBUG
		slavesMutex.lock();
		if(slaves->empty())
		{
			unique_lock<mutex> allListeningMutexLock(allListeningMutex);
			while(slaves->empty())
			{
				#ifdef _DEBUG2
				cout<<"slaves->empty()"<<endl;
				#endif // _DEBUG
				slavesMutex.unlock();
				allListeningCondition.wait(allListeningMutexLock);
				slavesMutex.lock();
			}
		}
		if(i>=slaves->size())
		{
			#ifdef _DEBUG2
			cout<<"slaves->size(): "<<slaves->size()<<endl;
			#endif // _DEBUG
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
				#ifdef _DEBUG2
				cout<<"allListeningCondition.wait(allListeningMutexLock)"<<endl;
				#endif // _DEBUG
				slavesMutex.unlock();
				unique_lock<mutex> allListeningMutexLock(allListeningMutex);
				allListeningCondition.wait(allListeningMutexLock);//niech sobie torchę zaczeka, aż pojawi sie nie słuchający agent
				#ifdef _DEBUG2
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
			#ifdef _DEBUG2
			cout<<"dodany wątek agenta IP: "<<slaves->at(i)->getSlaveIP()->getAddress()<<endl;
			#endif // _DEBUG
		}
		i++;
	}
}

void AgentServer::triggerShutDown()
{
	#ifdef _DEBUG
	cout<<"AgentServer::triggerShutDown()"<<endl;
	#endif // _DEBUG
	shutDown=true;
	slavesMutex.lock();
	for(unsigned int i=0;i<slaves->size();i++)
	{
		#ifdef _DEBUG
		cout<<"próbuję usunąć agenta: "<<slaves->at(i)->getSlaveIP()->getAddress()<< "z ConnectionManager..."<<endl;
		#endif // _DEBUG
		slavesMutex.unlock();
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
    if(tasks.find(task)==tasks.end())
    {
    	tasks.insert(task);
    }
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
			#ifdef _DEBUG2
			cout<<"czekam na zadanie..."<<endl;
			#endif // _DEBUG
			waitForTaskCondition.wait(waitForTaskMutexLock);
			#ifdef _DEBUG2
			cout<<"pojawiło się zadanie..."<<endl;
			#endif // _DEBUG
		}
		slavesMutex.lock();
		it=tasks.begin();
		for(unsigned int i=0;i<slaves->size();i++)
		{
			slavesMutex.unlock();
			#ifdef _DEBUG2
			cout<<"próbuję rozdysponować zadania do agentów i: "<<i<<" ..."<<endl;
			#endif // _DEBUG
            if(slaves->at(i)->ready && !slaves->at(i)->removed)/**< \todo zaznaczać agenta jako ready kiedy coś odpowie */
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
				//plik zawsze wysyłamy, jeśli tylko się pojawi
				if((*it)->name.size()>0)
				{
					message::Message* m=new message::fileMessage(message::State::REQ,true,(*it)->taskID,(*it)->name);
					connect(slaves->at(i),m);
				}
				if((*it)->taskState==TaskState::TASK_ADDED)
				{
					message::Message* m2=new message::taskMessage(message::TaskSub::T_ADD,message::State::REQ,true,1,(*it)->taskID,(*it)->when);
					connect(slaves->at(i),m2);
				}
				if((*it)->taskState==TaskState::RUN)
				{
					message::Message* m3=new message::taskMessage(message::TaskSub::T_RUN,message::State::REQ,true,1,(*it)->taskID,(*it)->when);
					connect(slaves->at(i),m3);
				}
				it++;

			}
			slavesMutex.lock();
		}
		#ifdef _DEBUG2
		cout<<"próba rozdzielenia zadań do agentów zakończona.."<<endl;
		#endif // _DEBUG
		slavesMutex.unlock();
		#ifdef _DEBUG2
		cout<<"begin waitForTaskCondition.wait_for(waitForTaskMutexLock,chrono::seconds(5))"<<endl;
		#endif // _DEBUG
		waitForTaskCondition.wait_for(waitForTaskMutexLock,chrono::seconds(5));
		#ifdef _DEBUG2
		cout<<"end waitForTaskCondition.wait_for(waitForTaskMutexLock,chrono::seconds(5))"<<endl;
		#endif // _DEBUG
	}

}

void AgentServer::setTaskFinished(unsigned long taskID)
{
	for(unsigned int i=0;i<slaves->size();i++)
	{
		if(slaves->at(i)->getTask()->taskID==taskID)
		{
			slaves->at(i)->getTask()->done=true;
			slaves->at(i)->getTask()->underExecution=false;
			slaves->at(i)->setTask(nullptr);
			slaves->at(i)->ready=true;
			unique_lock<mutex> allListeningMutexLock(allListeningMutex);
			allListeningMutexLock.unlock();
			allListeningCondition.notify_one();//odnowić nasłuchiwanie
		}
	}
	/*std::multiset<Task*,cmp>::iterator it;
	for(it=tasks.begin();!tasks.empty() && it!=tasks.end();it++)
	{
		if((*it)->taskID==taskID)
		{
			(*it)->done=true;
			(*it)->underExecution=false;
			break;
		}
	}*/

	unique_lock<mutex> waitForTaskMutexLock(waitForTaskMutex);
    waitForTaskMutexLock.unlock();
    waitForTaskCondition.notify_one();//przydzielić następne zadania
}

Task* AgentServer::getTaskByID(unsigned long taskID)
{
	std::multiset<Task*,cmp>::iterator it;
	for(it=tasks.begin();!tasks.empty() && it!=tasks.end();it++)
	{
		if((*it)->taskID==taskID)
		{
			return (*it);
			break;
		}
	}
	return nullptr;
}

void AgentServer::removeSlaveByIP(Ip* ip)
{
	slavesMutex.lock();
	for(unsigned int i=0;i<slaves->size();i++)
	{
		if((*(Ipv4*)ip)==*(Ipv4*)slaves->at(i)->getSlaveIP())
		{
			slavesMutex.unlock();
			#ifdef _DEBUG
			cout<<"próbuję usunąć agenta: "<<slaves->at(i)->getSlaveIP()->getAddress()<< "z ConnectionManager..."<<endl;
			#endif // _DEBUG
			slaves->at(i)->removed=true;
			connectionManager->remove(*(Ipv4*)slaves->at(i)->getSlaveIP());
			#ifdef _DEBUG
			cout<<"udało się usunąć agenta: "<<slaves->at(i)->getSlaveIP()->getAddress()<< "z ConnectionManager!"<<endl;
			#endif // _DEBUG
			slavesMutex.lock();
		}
	}
	slavesMutex.unlock();
}















