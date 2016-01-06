#include "Task.hpp"

Task::Task(std::string name, unsigned long taskId, std::chrono::steady_clock::time_point time)
{
    ready = false;
    state = IDLE;

    this->name = name;
    this->taskId = taskId;
    this->time = time;
}

void Task::run()
{
    if(ready)
    /**to do */

}

void Task::addFile(std::fstream file)
{
    /** to do*/
    ready = true;
}
