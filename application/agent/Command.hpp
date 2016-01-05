#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../protocol/ConnectionManager.hpp"
#include <iostream>

using namespace message;


class Command
{
    public:
    Command(){}
    ~Command(){}

    private:

};

class SynCommand: public Command
{
    public:
    SynCommand(Message *msg);
    private:

    synMessage sMessage;
};

class TaskCommand: public Command
{
    public:
    TaskCommand(Message *msg);

    private:

    taskMessage *tMessage;
};

class DepCommand: public Command
{
};

class FileCommand: public Command
{
    public:
    FileCommand(Message *msg);

    private:

    fileMessage *fMessage;
};

class PingCommand: public Command
{
    public:
    PingCommand(Message *msg);

    private:
    pingMessage *pMessage;
};


#endif
