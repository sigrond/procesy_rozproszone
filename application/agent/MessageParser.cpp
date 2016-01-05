#include "MessageParser.hpp"

using namespace message;

MessageParser::MessageParser(Message *msg)
{
    this->msg = msg;
}

void MessageParser::parse()
{
    unsigned char category, subCategory;
    category = msg->getCategory();

    switch(category)
    {
        case (int)Category::TASK:
        {
            TaskCommand taskCommand(msg);
            break;
        }
        case (int)Category::DEP:
        {
            //DepCommand depCommand(msg);
            break;
        }
        case (int)Category::FILE:
        {
            //FileCommand fileCommand(msg);
            break;
        }
        case (int)Category::SYN:
        {
            //SynCommand synCommand(msg);
            break;
        }
        case (int)Category::PING:
        {
            PingCommand pingCommand(msg);
            break;
        }
        default:
            std::cout << "default w słiczu" <<std::endl;
    }
}


