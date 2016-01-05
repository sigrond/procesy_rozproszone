#ifndef MessageParser_hpp
#define MessageParser_hpp

#include "../protocol/ConnectionManager.hpp"
#include "Command.hpp"
#include <iostream>

using namespace message;

class MessageParser
{


    public:
    MessageParser(Message * msg);
    ~MessageParser(){}

    void parse();

    private:
    Message* msg;
};



#endif
