/** \file AgentServer.h
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy serwera klienta / agenta
 *
 */

#pragma once

/** \brief klasa serwera agenta
 */
class AgentServer
{
public:
    AgentServer();
    void listen();/**< metoda nasłuchująca na połączenie z agentów. może być zrealizowana przez fork-server */
    void connect(auto who);/**< metoda łącząca się z agentem */
};
