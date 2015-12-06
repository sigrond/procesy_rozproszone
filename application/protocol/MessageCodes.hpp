#ifndef MESSAGE_CODES_HPP
#define MESSAGE_CODES_HPP

// nazwy kodowe dla kategorii, podkategorii, stanu komunikatu
// wartości dobrane tak, by suma kategoria + podkategoria + stan
// dawała własciwy kod zgodny z dokumentacją
namespace Message
{
        enum class Category = 
        {
                HOST    = 0x00,   // 000 000 00
                TASK    = 0x20,   // 001 000 00
                DEP     = 0x40,   // 010 000 00
                FILE    = 0x60,   // 011 000 00
                RET     = 0x80,   // 100 000 00
                SYN     = 0xA0,   // 101 000 00
                PING    = 0xC0,   // 110 000 00
                ERR     = 0xE0,   // 111 000 00
        };

        enum class State =
        {
                REQ     = 0x00,   // 000 000 00
                ACK     = 0x01,   // 000 000 01
                OK      = 0x02,   // 000 000 10
                ERR     = 0x03,   // 000 000 11
        };

        enum class HostSub =
        {
                H_ADD   = 0x00,   // 000 000 00
                H_RM    = 0x04,   // 000 001 00
                H_STATE = 0x08,   // 000 010 00
        };

        enum class TaskSub =
        {
                T_ADD   = 0x00,   // 000 000 00
                T_RM    = 0x04,   // 000 001 00
                T_RUN   = 0x08,   // 000 010 00
                T_KILL  = 0x0C,   // 000 011 00
                T_STOP  = 0x10,   // 000 100 00
                T_CONT  = 0x14,   // 000 101 00
                T_OK    = 0x18,   // 000 110 00
                T_NOK   = 0x1C,   // 000 111 00
        };

        enum class ErrSub =
        {
                E_HEAD  = 0x00,   // 000 000 00
                E_LGTH  = 0x04,   // 000 001 00
                E_CSUM  = 0x08,   // 000 010 00
                E_TASK  = 0x0C,   // 000 011 00
                E_FILE  = 0x10,   // 000 100 00


                E_OTH   = 0x1C,   // 000 111 00
        };
}
#endif // MESSAGE_CODES_HPP
