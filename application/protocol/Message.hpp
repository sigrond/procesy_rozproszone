/*
 * \file     Message.hpp
 *
 * \brief    Plik nagłówkowy klasy opakowującej komunikaty LOTC 
 * 
 * \version  0.3
 * \date     07.12.2015
 *
 * \author   Andrzej Roguski
 *
 * \todo     wyjątki
 * \todo     komantarze dokumentayjne
 * \todo     sekcje prywatne
 */

// WAŻNE : PEWNIE PODZIELĘ TEN PLIK NA MNIEJSZE JAK SIĘ ROZROŚNIE

// komentarze dokumentacyjne zrobię jak będę cierpiał na nadmiar czasu - raczej co robią konstruktory i gettery wszyscy wiedzą

// odnośnie konstruktorów - wersje z jednym argumentem są dla komunikatów ACK, OK i ERR

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <chrono>

#include "MessageCodes.hpp"
#include "Ip.hpp"

namespace message
{
        /**
         * \brief   Abstrakcyjna klasa bazowa obsługująca komunikaty LOTC
         */
        class Message
        {
        public:
                virtual ~Message();

                unsigned char getCode() const;
                
                unsigned char getCategory() const;

                unsigned char getState() const;

                unsigned char getSubcategory() const;

        private:
                virtual bool checkMessage () = 0 const;

                unsigned char code;
        };


        class hostMessage : public Message
        {
                hostMessage ( HostSub sub, State state, const std::vector<Ip> & addresses );

                hostMessage ( State state );

                unsigned short getAgentCount() const;

                std::vector<Ip> & getAddresses() const;
        };


        class taskMessage : public Message
        {
                taskMessage ( TaskSub sub,
                              State state,
                              bool respectPriority,
                              unsigned short priority,
                              unsigned long taskId,
                              const std::chrono::steady_clock::time_point & timestamp );

                taskMessage ( State state );

                bool getRespectPriority() const;

                unsigned short getPriority() const;

                unsigned long getTaskId() const;

                std::chrono::steady_clock::time_point & getTimestamp() const;
        };


        class depMessage : public Message
        {
                depMessage ( State state, std::vector<unsigned long> & tasks );

                depMessage ( State state );

                unsigned short getTaskCount() const;

                std::vector<unsigned long> & getTasks() const;
        };


        class fileMessage : public Message
        {
                fileMessage ( State state, bool isMainFile, unsigned long taskId, std::string filename, const std::ifstream & file );

                fileMessage ( State state );

                bool getIsMainFile() const;

                unsigned long getTaskId() const;

                std::string getFilename() const;

                std::ofstream & getFile() const;       
        };


        class retMessage : public Message
        {
                retMessage ( State state, unsigned char exitStatus, unsigned long taskId, std::string filename, const std::ifstream & file );

                retMessage ( State state );

                unsigned char getExitStatus() const;

                unsigned long getTaskId() const;

                std::string getFilename() const;

                std::ofstream & getFile() const;  
        };


        class synMessage : public Message
        {
                synMessage ( State state );
        };


        class pingMessage : public Message
        {
                pingMessage ( State state );
        };


        class errMessage : public Message
        {
        public:
                errMessage ( ErrSub sub, State state, unsigned char errCode );

                errMessage ( State state );

                unsigned char getErrCode () const;
        };

}

#endif // MESSAGE_HPP
