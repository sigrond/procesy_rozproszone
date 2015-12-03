/** \file Event.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy Event
 *
 */

#pragma once

/** \brief typy zdarzeń
 */
enum EventType
{
    Test
};

/** \brief Klasa reprezentująca zdarzenie.
 * Na rzecz szybkiego uzyskania działania aplikacji rezygnuję z pomysłu zrobienia
 * tej klasy wirtualną, gdyż powstaną przy tym ogromne niepoptrzebne problemy.
 */
class Event
{
public:
    Event();
    ~Event();
    EventType type;/**< typ zdarzenia pozwala wybrać właściwą metodę do jego obsługi */
    auto data;/**< dane niezbednę do zrealizowania metody obsługującej zdarzenie */
};
