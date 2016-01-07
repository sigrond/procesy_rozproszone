/**
 * Low Orbit Task Cannon
 *
 * \file     SocketException.hpp
 *
 * \brief    Wyjątki dla socketów
 *
 * \author   Andrzej Roguski
 *
 * \date     20.12.2015
 */

#ifndef SOCKET_EXCEPTION_HPP
#define SOCKET_EXCEPTION_HPP

#include <string>

/**
 * \brief Abstrakcyjna klasa bazowa wyjątków związanych z socketami
 */
class SockEx : public std::exception
{
public:
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept = 0;
	virtual ~SockEx();
};

/**
 * \brief Wyjątek: nieudane bind()
 */
class BindSockEx : public SockEx
{
public:
	BindSockEx();
	virtual ~BindSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: nieudane accept()
 */
class AcceptSockEx : public SockEx
{
public:
	AcceptSockEx();
	virtual ~AcceptSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: nieudane socket()
 */
class CreateSockEx : public SockEx
{
public:
	CreateSockEx();
	virtual ~CreateSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: nieudane listen()
 */
class ListenSockEx : public SockEx
{
public:
	ListenSockEx();
	virtual ~ListenSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: nieudane connect()
 */
class ConnectSockEx : public SockEx
{
public:
	ConnectSockEx();
	virtual ~ConnectSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: nieudane send()
 */
class SendSockEx : public SockEx
{
public:
	SendSockEx();
	virtual ~SendSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: nieudane receive()
 */
class RecSockEx : public SockEx
{
public:
	RecSockEx();
	virtual ~RecSockEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;

private:
	std::string error;
};

/**
 * \brief Wyjątek: timeout na receive()
 */
class TimeoutEx : public RecSockEx
{
public:
	TimeoutEx();
	virtual ~TimeoutEx();
	/**
	 * \brief  zwraca zakończony \0 komunikat o błędzie
	 * \return wzkaźnik na bufor z komunikatem
	 */
	virtual const char* what() const noexcept;
private:
	std::string error;
};

#endif // SOCKET_EXCEPTION_HPP
