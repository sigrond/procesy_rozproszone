/*
 * \file     SocketException.hpp
 *
 * \brief    Wyjątki dla socketów
 *
 * \author   Andrzej Roguski
 *
 */

#ifndef SOCKET_EXCEPTION_HPP
#define SOCKET_EXCEPTION_HPP

#include <string>

class SockEx : public std::exception
{
public:
        virtual const char* what() const noexcept = 0;
        virtual ~SockEx();
};



class BindSockEx : public SockEx
{
public:
        BindSockEx();
        virtual ~BindSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class AcceptSockEx : public SockEx
{
public:
        AcceptSockEx();
        virtual ~AcceptSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class CreateSockEx : public SockEx
{
public:
        CreateSockEx();
        virtual ~CreateSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class ListenSockEx : public SockEx
{
public:
        ListenSockEx();
        virtual ~ListenSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class ConnectSockEx : public SockEx
{
public:
        ConnectSockEx();
        virtual ~ConnectSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};

class TimeoutEx : public SockEx
{
public:
	TimeoutEx();
	virtual ~TimeoutEx();
	virtual const char* what() const noexcept;
private:
	std::string error;
};

#endif // SOCKET_EXCEPTION_HPP
