/** \file BlockingQueue.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy kolejki blokującej
 *
 */

#pragma once

#include <queue>

/** \brief kolejka blokująca. dziedziczy po queue.
 * żeby nie ryzykować użycia niezabezpieczonych wątkowo dziedziczonych metod
 * dziedziczenie po queue jest prywatne
 */
template <class T>
class BlockingQueue: private std::queue<T>
{
public:
    BlockingQueue();
    ~BlockingQueue();
    void push_back(T);
    T pop_front();
};
