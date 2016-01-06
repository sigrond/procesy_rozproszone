/*
 * \file     SocketException.cpp
 *
 * \brief    Wyjątki dla socketów
 *
 * \author   Andrzej Roguski
 *
 */

#include "SocketException.hpp"
#include <string.h>
#include <cerrno>

SockEx::~SockEx() {}


BindSockEx::~BindSockEx() {}

BindSockEx::BindSockEx()
{
        error = "Bind() error: ";
        error += strerror( errno );
}

const char * BindSockEx::what() const noexcept
{
        return error.c_str();
}


AcceptSockEx::~AcceptSockEx() {}

AcceptSockEx::AcceptSockEx()
{
        error = "Accept() error: ";
        error += strerror( errno );
}

const char * AcceptSockEx::what() const noexcept
{
        return error.c_str();
}


ConnectSockEx::~ConnectSockEx() {}

ConnectSockEx::ConnectSockEx()
{
        error = "Connect() error: ";
        error += strerror( errno );
}

const char * ConnectSockEx::what() const noexcept
{
        return error.c_str();
}


CreateSockEx::~CreateSockEx() {}

CreateSockEx::CreateSockEx()
{
        error = "Socket() error: ";
        error += strerror( errno );
}

const char * CreateSockEx::what() const noexcept
{
        return error.c_str();
}


ListenSockEx::~ListenSockEx() {}

ListenSockEx::ListenSockEx()
{
        error = "Listen() error: ";
        error += strerror( errno );
}

const char * ListenSockEx::what() const noexcept
{
        return error.c_str();
}


SendSockEx::~SendSockEx() {}

SendSockEx::SendSockEx()
{
        error = "Listen() error: ";
        error += strerror( errno );
}

const char * SendSockEx::what() const noexcept
{
        return error.c_str();
}



RecSockEx::~RecSockEx() {}

RecSockEx::RecSockEx()
{
        error = "Listen() error: ";
        error += strerror( errno );
}

const char * RecSockEx::what() const noexcept
{
        return error.c_str();
}

TimeoutEx::~TimeoutEx() {}

TimeoutEx::TimeoutEx()
{
	error = "Timeout on receive()";
}

const char * TimeoutEx::what() const noexcept
{
	return error.c_str();
}
