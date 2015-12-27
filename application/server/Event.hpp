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
    MESSAGE_FROM_MODEL,
    ADD_AGENT/**< ułatwiam sobie życie, bo utonę w metodach */
};

/** \brief Klasa reprezentująca zdarzenie.
 * Na rzecz szybkiego uzyskania działania aplikacji rezygnuję z pomysłu zrobienia
 * tej klasy wirtualną, gdyż powstaną przy tym ogromne niepoptrzebne problemy.
 */
class Event
{
public:
    Event() : type(Test), data(nullptr)
    {

    }
    Event(EventType t) : type(t), data(nullptr)
    {

    }
    Event(EventType t, void* d) : type(t), data(d)
    {

    }
    ~Event()
    {
		#ifdef _DEBUG
		std::cout<<"~Event "<<type<<" "<<data<<"\n";
		#endif // _DEBUG
    }
    EventType type;/**< typ zdarzenia pozwala wybrać właściwą metodę do jego obsługi */
    void* data;/**< dane niezbednę do zrealizowania metody obsługującej zdarzenie */
};
