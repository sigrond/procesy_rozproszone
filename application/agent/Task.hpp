#ifndef TASK_HPP
#define TASK_HPP

#include <fstream>
#include <chrono>
#include <string>
namespace TaskState
{
	enum TaskState
	{
		WAIT,/**< było polecenie uruchomienia, ale jeszcze nie minął czas */
		RUN,/**< zadanie uruchomione */
		IDLE /**< zadanie nic nie robi */
	};
}

class Task
{
    public:
    Task(std::string name, unsigned long taskId, std::chrono::steady_clock::time_point time);

    void run();
    void addFile(std::fstream file);

    private:

    /**czy został dodany plik do zadania? true - tak, zadanie gotowe; false - zadanie nie gotowe */
    bool ready;

    TaskState state;
    std::string name;
    std::fstream file;
    unsigned long taskId;
    std::chrono::steady_clock::time_point time;

};





















#endif // TASK_HPP
