/*
 * \file     Message.hpp
 *
 * \brief    Plik nagłówkowy klasy opakowującej komunikaty LOTC 
 * 
 * \version  0.1
 * \date     06.12.2015
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

#include "MessageCodes.hpp"
#include "Ip.hpp"

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
                bool checkMessage () = 0 const;

                unsigned char code;
        };

        class hostMessage
        {

        };

        class taskMessage
        {

        };

        class depMessage
        {

        };

        class fileMessage
        {

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
