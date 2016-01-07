/** \file MessageParser.cpp
 * \authors Eryk Ratyński, Tomasz Jakubczyk
 * \brief Plik z deklaracją klasy MessageParser
 * \date 5 sty 2015
 * Low Orbit Task Cannon
 */

#ifndef MessageParser_hpp
#define MessageParser_hpp

#include "../protocol/ConnectionManager.hpp"
#include "../server/BlockingQueue.hpp"
#include "Command.hpp"
#include <iostream>

using namespace message;

class MessageParser
{


    public:
    MessageParser(Message * msg,BlockingQueue<message::Message*>* q);
    ~MessageParser(){}

    void parse();

    private:
    Message* msg;
    BlockingQueue<message::Message*>* q;
};



#endif
