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
	/**< w sumie mozna było użyć operator(), było by to chyba bardziej intuicyjne */
    virtual void doJob(void* data, void* who=nullptr,unsigned short port=0) = 0;/**< sposób realizacji danej strategii */
};
