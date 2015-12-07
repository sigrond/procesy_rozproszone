/*
 * \file     Message.hpp
 *
 * \brief    Plik nagłówkowy klasy opakowującej komunikaty LOTC 
 * 
 * \version  0.2
 * \date     07.12.2015
 *
 * \author   Andrzej Roguski
 *
 * \todo     reszta interfejsu
 * \todo     wyjątki
 * \todo     komantarze
 * \todo     sekcje prywatne
 */

// WAŻNE : PEWNIE PODZIELĘ TEN PLIK NA MNIEJSZE JAK SIĘ ROZROŚNIE

// INTERFEJS NIEKOMPLETNY


#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>

#include "MessageCodes.hpp"
#include "Ip.hpp"

namespace clock std::chrono::steady_clock;

namespace Message
{

        class Message
        {
        public:
                Message ( unsigned char code );

                virtual ~Message();

                unsigned char getCode() const;
                
                unsigned char getCategory() const;

                unsigned char getState() const;

                unsigned char getSubcategory() const;

        private:
                virtual bool checkMessage () = 0 const;

                unsigned char code;
        };

        class hostMessage
        {
                hostMessage ( HostSub sub, State state, const std::vector<Ip> & addresses );

                unsigned short getAgentCount() const;

                std::vector<Ip> & getAddresses() const;
        };

        class taskMessage
        {
                taskMessage ( TaskSub sub,
                              State state,
                              bool respectPriority,
                              unsigned short priority,
                              unsigned int taskId,
                              const clock::time_point & timestamp );

                bool getRespectPriority();

                unsigned short getPriority() const;

                unsigned int getTaskId() const;

                unsigned int getTaskId() const;

                clock::time_point & getTimestamp() const;
        };

        class depMessage
        {
                depMessage ( State state, std::vector<unsigned int> & tasks );

                unsigned short getTaskCount();

                std::vector<unsigned int> & getTasks();
        };

        class fileMessage
        {
                fileMessage ( State state, bool isMainFile, unsigned int taskId, std::string filename, const std::ifstream & file );

                bool getIsMainFile();

                unsigned int getTaskId();

                std::string getFilename();

                std::ofstream & getFile();       
        };

        class retMessage
        {

        };

        class synMessage
        {
                synMessage ( State state );
        };

        class pingMessage
        {
                pingMessage ( State state );
        };

        class errMessage
        {
        public:
                errMessage ( ErrSub sub, State state, unsigned char errCode );

                unsigned char getErrCode () const;
        };

}
#endif
