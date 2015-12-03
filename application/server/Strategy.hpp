/** \file Strategy.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy abstrakcyjnej klasy Strategy.
 *
 */

#pragma once

/** \brief Wirtualna klasa strategii obsługi zdarzenia.
 * Klasę należy zkonkretyzować dziedzicząc po niej np. AdminServerStrategy
 */
class Strategy
{
public:
    virtual void doJob() = 0;/**< sposób realizacji danej strategii */
};
