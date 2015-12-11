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
#include <iostream>
#include <string>
#include <thread>


/** \brief Testowa klasa strategii.
 * Ma służyć jako zaślepka do brakujących klas strategii,
 * oraz ewentualnie jako klasa pozwalająca systemowi na samodiagnozę.
 */
class TestStrategy : public Strategy
{
public:
	TestStrategy() : ObjectID(createdObjects)
	{
		createdObjects++;
	}
	~TestStrategy()
	{
		deletedObjects++;
	}
	virtual void doJob(void* data) override
	{
		std::clog<<"TestStrategy, ObjectID: "<<ObjectID
				<<", createdObjects: "<<createdObjects
				<<", deletedObjects: "<<deletedObjects
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

/**< \todo Napisać więcej strategii, jak już będzie wiadomo co mają robić */


























