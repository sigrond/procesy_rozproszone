/** \file Task.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Task.
 * \date
 * Low Orbit Task Cannon
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
	name=s;
	#ifdef _DEBUG
	cout<<"Task::Task(string s) name: "<<name<<endl;
	#endif // _DEBUG
	/**< \todo jakoś sparsować czas, jeśli bedzie podany po nazwie */
	when=chrono::steady_clock::now();
	//file.open(name.c_str(), std::fstream::in);
}

Task::~Task()
{
	//dtor
}
