/** \file BlockingQueue.cpp
 * \author Tomasz Jakubczyk
 * \brief Implementacja metod BlockingQueue
 *
 */

#include "BlockingQueue.hpp"
#include <iostream>

BlockingQueue::BlockingQueue()
{
#ifdef _DEBUG
    std::cout<<"BlockingQueue::BlockingQueue()\n";
#endif // _DEBUG
}

BlockingQueue::~BlockingQueue()
{
#ifdef _DEBUG
    std::cout<<"BlockingQueue::~BlockingQueue()\n";
#endif // _DEBUG
}

template <class T>
void BlockingQueue::push_back(const T& element)
{
    std::unique_lock<std::mutex> mutexLock(m);
    q.push(element);
    mutexLock.unlock();
    c.notify_one();
}

template <class T>
T BlockingQueue::pop_front()
{
    T element;
    std::unique_lock<std::mutex> mutexLock(m);
    while(q.empty())
    {
        c.wait(mutexLock);
    }
    element=q.front();
    q.pop();
    return element;
}






















