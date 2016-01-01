/** \file Strategies.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik ze wszystkimi strategiami.
 * Z powodu małej złożoności strategii nie wydzielamy osobnych plików na każdą klasę
 * strategii dziedziczącej po Strategy. Dodatkowo nie rozdzielamy deklaracji od definicji.
 * Jeśli w puźniejszych fazach projektu okaże się, że jednak klasy strategii się rozrosną,
 * co jest bardzo mało prawdopodobne, to powinno się podzielić ten plik na więcej plików,
 * dla każdej klasy osobny.
 */

#pragma once

#include "Strategy.hpp"
#include "Controller.hpp"
#include "../protocol/Message.hpp"
#include "../protocol/Ip.hpp"
#include "AgentServer.hpp"
#include "Task.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <fstream>


/** \brief Testowa klasa strategii.
 * Ma służyć jako zaślepka do brakujących klas strategii,
 * oraz ewentualnie jako klasa pozwalająca systemowi na samodiagnozę.
 */
class TestStrategy : public Strategy
{
public:
	TestStrategy() : Strategy(nullptr), ObjectID(createdObjects)
	{
		createdObjects++;
	}
	TestStrategy(void* v) : Strategy(v), ObjectID(createdObjects)
	{
		createdObjects++;
	}
	virtual ~TestStrategy()
	{
		deletedObjects++;
	}
	virtual void doJob(void* data) override
	{
		std::clog<<"TestStrategy, ObjectID: "<<ObjectID
		//		<<", createdObjects: "<<createdObjects
		//		<<", deletedObjects: "<<deletedObjects
				<<", data: "<<data<<std::endl;
	}
	static int createdObjects;
	static int deletedObjects;
private:
	const int ObjectID;
};

/** \brief Strategia kończenia pracy serwera.
 */
class ShutDownStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief metoda zamykająca serwer
     * \param data Controller* niech strategia wie jaki serwer zamknąc,
     * przez podanie wskaźnika na serwer do zamknięcia
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		std::cout<<"Zamykanie serwera...\n";
		((Controller*)data)->triggerShutDown();
	}
};

/** \brief Strategia przetwarzania i obsługi wiadomości od administratora.
 */
class MessageFromAdminStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief obsługa wiadomości od admina
     *
     * \param data message::Message*
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		using namespace std;
		using namespace message;
		unsigned char category, subCategory;
		hostMessage* hm;
		unsigned int hostsNumber;
		std::vector<Ip>* agentIPs;
		taskMessage* tm;
		fileMessage* fm;
		string name;
		fstream file;
		category=((Message*)data)->getCategory();
		switch(category)/**< \todo obsługa kategorii */
		{
		case (int)Category::HOST:
			//dodawanie agenta
			hm=(hostMessage*)data;
			subCategory=hm->getSubcategory();
            hostsNumber=hm->getAgentCount();
            agentIPs=&hm->getAddresses();
			if(subCategory==(unsigned char)HostSub::H_ADD)
			{
				for(unsigned int i=0;i<hostsNumber;i++)
				{
					((Controller*)controller)->blockingQueue->push_back(new Event(ADD_AGENT,&agentIPs->at(i)));
				}
			}
			/**< \todo usuwanie agentów */
			/**< \todo sprawdzanie stanu agentów */
			break;
		case (int)Category::TASK:
			//zlecenie wykonania zadania
			tm=(taskMessage*)data;
			subCategory=tm->getSubcategory();
			//dodanie zadania
			if(subCategory==(unsigned char)TaskSub::T_ADD)
			{
				/**< \todo znaleźć plik i dodać do zadań */
			}
			//uruchomienie zadania
			else if(subCategory==(unsigned char)TaskSub::T_RUN)
			{

			}
			/**< \todo pozostałe podkategorie task */
			break;
		case (int)Category::DEP:
			break;
		case (int)Category::FILE:
			fm=(fileMessage*)data;
			/**< \todo zapisać plik na dysku */
			//tutaj raczej nie znamy id zadania, bo dopiero na podstawie tego pliku go utworzymy dodając zadanie
			name=fm->getFilename();
			file.open(name.c_str());/**< \todo za mało wiadomości o niekompletnej klasie fileMessage */

			/**< \todo trzeba ustalić co dokładnie może zrobić administrator */
			break;
		case (int)Category::RET:
			break;
		case (int)Category::SYN:
			break;
		case (int)Category::PING:
			break;
		case (int)Category::ERR:
			break;
		default:
			clog<<"Nieznana kategoria wiadomości od admina: "<<category<<endl;
		}
	}
};

class MessageFromAgentStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief obsługa wiadomości od agenta
     *
     * \param data message::Message*
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		using namespace std;
		using namespace message;
		unsigned char category, subCategory;
		category=((Message*)data)->getCategory();
		taskMessage* tm;
		fileMessage* fm;
		retMessage* rm;
		unsigned char exitStatus;
		unsigned long taskID;
		string name;
		ofstream file;
		switch(category)/**< \todo obsługa kategorii */
		{
		case (int)Category::HOST:
			break;
		case (int)Category::TASK:
			//odbieranie komunikatów od agentów
			tm=(taskMessage*)data;
			subCategory=tm->getSubcategory();
			//zadanie gotowe do przetwarzania
			if(subCategory==(unsigned char)TaskSub::T_OK)
			{
				/**< \todo wysłać task run */
			}
			else if(subCategory==(unsigned char)TaskSub::T_NOK)
			{
				/**< \todo yyy, nic nie robić? */
			}
			break;
		case (int)Category::DEP:
			break;
		case (int)Category::FILE:
			fm=(fileMessage*)data;
			// chyba odesłać do administratora
			((Controller*)controller)->adminServer->connect((Message*)data);
			break;
		case (int)Category::RET:
			//odbieranie wyników zadań
			rm=(retMessage*)data;
			/**< \todo włąściwie to całą tą wiadomość można wysłać adminowi i tylko zaznaczyć, zadanie jako wykonane */
			exitStatus=rm->getExitStatus();//to chyba tylko obchodzi administratora
			/**< \todo odesłać status zakończenia do admina */
			taskID=rm->getTaskId();
			//zaznaczamy zadanie jako wykonane
			((Controller*)controller)->agentServer->setTaskFinished(taskID);
			name=rm->getFilename();
			//file=rm->getFile();
			//odsyłamy wiadomość
			((Controller*)controller)->adminServer->connect((Message*)data);
			break;
		case (int)Category::SYN:
			break;
		case (int)Category::PING:
			break;
		case (int)Category::ERR:
			break;
		default:
			clog<<"Nieznana kategoria wiadomości od agenta: "<<category<<endl;
		}
	}
};

class AddAgentStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief obsługa dodania agenta
     *
     * \param data message::Message*
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		using namespace std;
        cout<<"strategia AddAgent..."<<endl;
        //AgentServer* as=((Controller*)((pair<void*,void*>*)data)->second)->agentServer;
        AgentServer* as=((Controller*)controller)->agentServer;
        //Ipv4 ip=*(Ipv4*)((pair<void*,void*>*)data)->first;
        Ipv4* ip=(Ipv4*)data;
        as->addSlave(ip);
        //delete (pair<void*,void*>*)data;
	}
};


class PingAdminStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief obsługa pingowania admina
     *
     * \param data message::Message*
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		using namespace std;
		using namespace message;
        cout<<"strategia PingAdmin..."<<endl;
        Message * msg2 = new pingMessage( State::REQ );
        ((Controller*)controller)->adminServer->connect(msg2);
	}
};

class PingSlavesStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief obsługa pingowania agenta
     *
     * \param data message::Message*
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		using namespace std;
		using namespace message;
        cout<<"strategia PingSlaves..."<<endl;
        Message * msg2 = new pingMessage( State::REQ );
        ((Controller*)controller)->agentServer->sendToAll(msg2);
	}
};

class AddTaskStrategy : public Strategy
{
public:
	using Strategy::Strategy;
    /** \brief obsługa dodania zadania
     *
     * \param data message::Message*
     * \return virtual void
     *
     */
	virtual void doJob(void* data) override
	{
		using namespace std;
        cout<<"strategia AddTask..."<<endl;
		((Controller*)controller)->agentServer->addTask((Task*)data);
	}
};


/**< \todo Napisać więcej strategii, jak już będzie wiadomo co mają robić */

























