#include "MessageParser.hpp"

using namespace message;

MessageParser::MessageParser(Message *msg,BlockingQueue<message::Message*>* q) : q(q)
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
            TaskCommand taskCommand(msg,q);
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
            PingCommand pingCommand(msg,q);
            break;
        }
        default:
            std::cout << "default w słiczu" <<std::endl;
    }
}

