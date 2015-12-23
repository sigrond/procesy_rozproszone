/*
 * \file     SocketException.hpp
 *
 * \brief    Wyjątki dla socketów
 *
 * \author   Andrzej Roguski
 *
 */

#include "SocketException.hpp"
#include <string.h>

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
