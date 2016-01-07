/** \file Command.hpp
 * \authors Eryk Ratyński, Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy Command
 * \date 5 sty 2015
 * Low Orbit Task Cannon
 */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../protocol/ConnectionManager.hpp"
#include "../server/BlockingQueue.hpp"
#include <iostream>

using namespace message;


class Command
{
    public:
    Command(BlockingQueue<message::Message*> *q) : q(q)
    {}
    ~Command(){}
    protected:
    BlockingQueue<message::Message*>* q;
    private:

};

class SynCommand: public Command
{
    public:
    SynCommand(Message *msg,BlockingQueue<message::Message*> *q);
    private:

    synMessage sMessage;
};

class TaskCommand: public Command
{
    public:
    TaskCommand(Message *msg,BlockingQueue<message::Message*> *q);

    private:

    taskMessage *tMessage;
};

class DepCommand: public Command
{
};

class FileCommand: public Command
{
    public:
    FileCommand(Message *msg,BlockingQueue<message::Message*> *q);

    private:

    fileMessage *fMessage;
};

class PingCommand: public Command
{
    public:
    PingCommand(Message *msg,BlockingQueue<message::Message*> *q);

    private:
    pingMessage *pMessage;
};


#endif
