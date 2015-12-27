/** \file Strategy.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy abstrakcyjnej klasy Strategy.
 *
 */

#pragma once

#include <iostream>

/** \brief Wirtualna klasa strategii obsługi zdarzenia.
 * Klasę należy zkonkretyzować dziedzicząc po niej np. AdminServerStrategy
 */
class Strategy
{
public:
	void* controller;
	Strategy():controller(nullptr)
	{
		#ifdef _DEBUG
		std::cout<<"Strategy()"<<std::endl;
		#endif // _DEBUG
	};
	Strategy(void* c):controller(c)
	{
		#ifdef _DEBUG
		std::cout<<"Strategy(Controller* c)"<<std::endl;
		#endif // _DEBUG
	};
    virtual void doJob(void* data) = 0;/**< sposób realizacji danej strategii */
};
