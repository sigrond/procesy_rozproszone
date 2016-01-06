/*
 * \file     Message.hpp
 *
 * \brief    Plik nagłówkowy klasy opakowującej komunikaty LOTC
 *
 * \version  0.3
 * \date     07.12.2015
 *
 * \authors   Andrzej Roguski, Tomasz Jakubczyk
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
#include <fstream>

#include "MessageCodes.hpp"
#include "Ip.hpp"

namespace message
{

        class Message
        {
        public:
		Message( Category category );

		Message( Category category, unsigned long bufferSize );

		Message( Category category, State state );

                virtual ~Message();

                unsigned char getCode() const;

                unsigned char getCategory() const;

                unsigned char getState() const;

                unsigned char getSubcategory() const;

		char * getBuffer() const;

		unsigned long getBufferSize() const;

		void print() const;

        protected:
                virtual bool checkMessage () const; //= 0; TYLKO TYMCZASOWO, BO JEST TO SZYBSZE NIŻ PISANIE METODY DLA 8 PODKLAS

                unsigned char code;

		char * buffer;

		unsigned long bufferSize;
        };

//------------------------------
// hostMessage
//------------------------------
        class hostMessage : public Message
        {
        public:
                hostMessage ( HostSub sub, State state, const std::vector<Ipv4> & addresses );

                hostMessage ( State state );

                unsigned short getAgentCount() const;

                std::vector<Ipv4> & getAddresses();
	
	private:
		std::vector<Ipv4> addresses;
        };

//------------------------------
// taskMessage
//------------------------------
        class taskMessage : public Message
        {
        public:
                taskMessage ( TaskSub sub,
                              State state,
                              bool respectPriority,
                              unsigned short priority,
                              unsigned long taskId,
                              const std::chrono::steady_clock::time_point & timestamp );

                taskMessage ( State state );

                bool getRespectPriority();

                unsigned short getPriority() const;

                unsigned long getTaskId() const;

                std::chrono::steady_clock::time_point getTimestamp() const;
	
	private:
		TaskSub taskSub;
		bool respectPriority;
		unsigned short priority;
		unsigned long taskId;
		std::chrono::steady_clock::time_point time;
        };

//------------------------------
// depMessage
//------------------------------
        class depMessage : public Message
        {
        public:
                depMessage ( State state, std::vector<unsigned long> & tasks );

		depMessage ( char * buffer, unsigned long bufferSize );

                depMessage ( State state );

                unsigned short getTaskCount();

                std::vector<unsigned long> & getTasks();
	
	private:
		std::vector<unsigned long> tasks;
        };

//------------------------------
// fileMessage
//------------------------------
        class fileMessage : public Message
        {
        public:
                fileMessage ( State state, bool isMainFile, unsigned long taskId, std::string filename );

                fileMessage ( State state );

                bool getIsMainFile();

                unsigned long getTaskId();

                std::string getFilename();

	private:
		bool isMainFile;
		unsigned long taskId;
		std::string name;
        };

//------------------------------
// retMessage
//------------------------------
        class retMessage : public Message
        {
        public:
                retMessage ( State state, unsigned char exitStatus, unsigned long taskId, std::string filename);

                retMessage ( State state );

                unsigned char getExitStatus();

                unsigned long getTaskId();

                std::string getFilename();

                std::fstream & getFile();
		
	private:
		unsigned char exitStatus;
		unsigned long taskId;
		std::string name;
		std::fstream file;
        };

//------------------------------
// synMessage
//------------------------------
        class synMessage : public Message
        {
        public:
                synMessage ( State state );

        };

//------------------------------
// pingMessage
//------------------------------
        class pingMessage : public Message
        {
        public:
                pingMessage ( State state );

        };

//------------------------------
// errMessage
//------------------------------
        class errMessage : public Message
        {
        public:
                errMessage ( ErrSub sub, State state, unsigned char errCode );

                errMessage ( State state );

                unsigned char getErrCode () const;
	
	private:
		unsigned char errCode;
        };

}
#endif // MESSAGE_HPP
