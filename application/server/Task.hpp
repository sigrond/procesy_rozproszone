/** \file Task.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy Task.
 *
 */

#pragma once

#include <string>
#include <chrono>
#include <fstream>

namespace TaskState
{
	enum TaskState
	{
		FILE_ADDED,/**< został dodany plik zadania, ale nie było polecenia dodania zadania */
		TASK_ADDED,/**< było polecenie dodania zadania */
		RUN,/**< było polecenie wykonania zadania */
	};
}

/** \brief Klasa odpowiadająca za przechowywanie informacji o zadaniu.
 */
class Task
{
public:
	/** Default constructor */
	Task();
	Task(std::string s);
	/** Default destructor */
	~Task();
	std::string name;/**< nazwa pliku z zadaniem? */
	std::chrono::steady_clock::time_point when;
	//std::chrono::system_clock::time_point when;/**< kiedy zadanie ma być wykonane? */
	bool done;/**< zadanie wykonane */
	bool underExecution;/**< zadanie w trakcie wykonywania, lub zlecone agentowi */
	unsigned long taskID;
	static unsigned long taskCounter;
	std::fstream file;
	TaskState::TaskState taskState;
protected:
private:
};
