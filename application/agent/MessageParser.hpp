#ifndef MessageParser_hpp
#define MessageParser_hpp

#include "../protocol/ConnectionManager.hpp"
#include "Command.hpp"

namespace message
{
class MessageParser
{


    public:
    MessageParser(Message *msg);
    ~MessageParser(){}

    void parse();

    private:
    Message* msg;
};
}


#endif
