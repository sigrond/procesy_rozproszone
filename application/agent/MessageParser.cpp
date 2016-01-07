#include "MessageParser.hpp"
#include <iostream>

using namespace std;
using namespace message;

MessageParser::MessageParser(Message *msg,BlockingQueue<message::Message*>* q) : q(q)
{
    this->msg = msg;
}

void MessageParser::parse()
{
	#ifdef _DEBUG
	cout<<"MessageParser::parse()"<<endl;
	#endif // _DEBUG
    unsigned char category, subCategory;
    category = msg->getCategory();

    switch(category)
    {
        case (int)Category::TASK:
        {
        	#ifdef _DEBUG
        	cout<<"odebrana wiadomość  jest Category::TASK"<<endl;
        	#endif // _DEBUG
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
        	#ifdef _DEBUG
        	cout<<"odebrana wiadomość  jest Category::PING"<<endl;
        	#endif // _DEBUG
            PingCommand pingCommand(msg,q);
            break;
        }
        default:
            std::cout << "default w słiczu" <<std::endl;
    }
}


