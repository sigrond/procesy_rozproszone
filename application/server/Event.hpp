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
    Test,
    SHUT_DOWN,
    MESSAGE_FROM_ADMIN_SERVER,
    MESSAGE_FROM_AGENT_SERVER,
    MESSAGE_FROM_MODEL
};

/** \brief Klasa reprezentująca zdarzenie.
 * Na rzecz szybkiego uzyskania działania aplikacji rezygnuję z pomysłu zrobienia
 * tej klasy wirtualną, gdyż powstaną przy tym ogromne niepoptrzebne problemy.
 */
class Event
{
public:
    Event()
    {

    }
    ~Event()
    {

    }
    EventType type;/**< typ zdarzenia pozwala wybrać właściwą metodę do jego obsługi */
    void* data;/**< dane niezbednę do zrealizowania metody obsługującej zdarzenie */
};
