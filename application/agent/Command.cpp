#include "Command.hpp"

using namespace message;

TaskCommand::TaskCommand(Message *msg)
{
    this->tMessage = static_cast<taskMessage*>(msg);
    /**sprawdzam kategorie polecenia */
    unsigned char subCategory = tMessage->getSubcategory();
    unsigned char msgState = tMessage->getState();

    switch( subCategory)
    {
        case (int)TaskSub::T_ADD:
        {
            if(msgState == (unsigned char)State::REQ)
            {
                //dostalismy nowe zadanie, trzeba je dodac, trzeba wyslac ACK,
                //po dodaniu zadania wyslac OK lub NOK
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

            break;
        }
        case (int)TaskSub::T_RM:
        {

            if(msgState == (unsigned char)State::REQ)
            {
                //dostalismy polecenie usuniecia zadania, wyslac ACK
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

            break;
        }

    }


}

FileCommand::FileCommand(Message *msg)
{
    this->fMessage = static_cast<fileMessage*>(msg);


}




PingCommand::PingCommand(Message *msg)
{
    this->pMessage = static_cast<pingMessage*>(msg);

    /**TO DO sprawdzic stan wiadomosci*/

}



