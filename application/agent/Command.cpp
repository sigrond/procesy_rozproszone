#include "Command.hpp"

using namespace message;

TaskCommand::TaskCommand(Message *msg,BlockingQueue<message::Message*> *q) : Command(q)
{
    this->tMessage = static_cast<taskMessage*>(msg);
    /**sprawdzam kategorie polecenia */
    unsigned char subCategory = tMessage->getSubcategory();
    unsigned char msgState = tMessage->getState();
    taskMessage* tm=nullptr;

    switch( subCategory)
    {
        case (int)TaskSub::T_ADD:
        {
            if(msgState == (unsigned char)State::REQ)
            {
                //dostalismy nowe zadanie, trzeba je dodac, trzeba wyslac ACK,
                //po dodaniu zadania wyslac OK lub NOK
                tm=new taskMessage(TaskSub::T_ADD,State::ACK,tMessage->getRespectPriority(),tMessage->getPriority(),tMessage->getTaskId(),tMessage->getTimestamp());
                q->push_back(tm);
            }else
            {
                std::cout << "zła kategoria stanu" << std::endl;
            }

            break;
        }
        case (int)TaskSub::T_RUN:
        {
            if(msgState == (unsigned char)State::REQ)
            {
                //dostalismy polecenie uruchomienia zadania, wyslac ACK
                tm=new taskMessage(TaskSub::T_RUN,State::ACK,tMessage->getRespectPriority(),tMessage->getPriority(),tMessage->getTaskId(),tMessage->getTimestamp());
                q->push_back(tm);
                //po odpaleniu wątku uruchomienia zadania wyslacOK lub NOK

            }else if (msgState == (unsigned char)State::ACK)
            {
                //poprawnie otrzymal wiadomosc OK lub NOK?
            }else
            {
                std::cout << "zła kategoria komunikatu/stanu" << std::endl;
            }

            break;
        }
        case (int)TaskSub::T_STOP:
        {
			tm=new taskMessage(TaskSub::T_STOP,State::ACK,tMessage->getRespectPriority(),tMessage->getPriority(),tMessage->getTaskId(),tMessage->getTimestamp());
			q->push_back(tm);
            break;
        }
        case (int)TaskSub::T_RM:
        {

            if(msgState == (unsigned char)State::REQ)
            {
                //dostalismy polecenie usuniecia zadania, wyslac ACK
                tm=new taskMessage(TaskSub::T_RM,State::ACK,tMessage->getRespectPriority(),tMessage->getPriority(),tMessage->getTaskId(),tMessage->getTimestamp());
                q->push_back(tm);
                //po usunieciu zadania wyslacOK lub NOK

            }else if (msgState == (unsigned char)State::ACK)
            {
                //poprawnie otrzymal wiadomosc OK lub NOK, wiec nic nie robimy?
            }else
            {
                std::cout << "zła kategoria komunikatu/stanu" << std::endl;
            }

            break;
        }
        case (int)TaskSub::T_KILL:
        {
			if(msgState == (unsigned char)State::REQ)
            {
                //dostalismy polecenie usuniecia zadania, wyslac ACK
                tm=new taskMessage(TaskSub::T_KILL,State::ACK,tMessage->getRespectPriority(),tMessage->getPriority(),tMessage->getTaskId(),tMessage->getTimestamp());
                q->push_back(tm);
                //po usunieciu zadania wyslacOK lub NOK

            }else if (msgState == (unsigned char)State::ACK)
            {
                //poprawnie otrzymal wiadomosc OK lub NOK, wiec nic nie robimy?
            }else
            {
                std::cout << "zła kategoria komunikatu/stanu" << std::endl;
            }
            break;
        }

    }


}

FileCommand::FileCommand(Message *msg,BlockingQueue<message::Message*> *q) : Command(q)
{
    this->fMessage = static_cast<fileMessage*>(msg);


}




PingCommand::PingCommand(Message *msg,BlockingQueue<message::Message*> *q) : Command(q)
{
    this->pMessage = static_cast<pingMessage*>(msg);

    /**TO DO sprawdzic stan wiadomosci*/

}



