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
};



class BindSockEx : public SockEx
{
public:
        BindSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class AcceptSockEx : public SockEx
{
public:
        AcceptSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class CreateSockEx : public SockEx
{
public:
        CreateSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class ListenSockEx : public SockEx
{
public:
        ListenSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};



class ConnectSockEx : public SockEx
{
public:
        ConnectSockEx();
        virtual const char* what() const noexcept;

private:
        std::string error;
};

#endif // SOCKET_EXCEPTION_HPP
