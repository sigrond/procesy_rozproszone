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
    ADD_AGENT,/**< ułatwiam sobie życie, bo utonę w metodach */
    PING_ADMIN,
    PING_SLAVES,
    ADD_TASK
};

/** \brief Klasa reprezentująca zdarzenie.
 * Na rzecz szybkiego uzyskania działania aplikacji rezygnuję z pomysłu zrobienia
 * tej klasy wirtualną, gdyż powstaną przy tym ogromne niepoptrzebne problemy.
 */
class Event
{
public:
    Event() : type(Test), data(nullptr), who(nullptr)
    {

    }
    Event(EventType t) : type(t), data(nullptr), who(nullptr)
    {

    }
    Event(EventType t, void* d) : type(t), data(d), who(nullptr)
    {

    }
    Event(EventType t, void* d, void* w) : type(t), data(d), who(w)
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
    void* who;/**< dodatkowe opcjonalne pole mówiące od kogo jest Event */
};
