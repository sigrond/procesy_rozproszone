/** \file Task.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Task.
 *
 */

#include "Task.hpp"
#include <iostream>

using namespace std;

unsigned long Task::taskCounter=0;

Task::Task() : done(false), underExecution(false), taskID(taskCounter)
{
	taskCounter++;
}

Task::Task(string s) : Task()
{
	#ifdef _DEBUG
	cout<<"Task::Task(string s) name: "<<name<<endl;
	#endif // _DEBUG
	/**< \todo jakoś sparsować czas, jeśli bedzie podany po nazwie */
	name=s;
	when=chrono::steady_clock::now();
	file.open(name.c_str(), std::ifstream::in);
}

Task::~Task()
{
	//dtor
}
