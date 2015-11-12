#include "message.hpp" 
#include <iostream>

TestMessage::TestMessage(TestMessage::Code code, int first, int second) : code(code)
{    
        numbers[0] = first;
        numbers[1] = second; 
}

TestMessage::~TestMessage()
{
}

char* TestMessage::send(char* buf)
{              
        *buf = code;

        std::copy(reinterpret_cast<const char*>(numbers),
                  reinterpret_cast<const char*>(numbers) + sizeof(int),
                  buf+1);

        std::copy(reinterpret_cast<const char*>(numbers+1),
                  reinterpret_cast<const char*>(numbers+1) + sizeof(int),
                  buf+5);

        return buf;

}

void TestMessage::receive(char* buf)
{
        numbers[0] = 0;
        numbers[1] = 0;

        code = (Code)*buf;
        
        for(int j = 0; j<2; j++)
                for(int i = 1; i<5; i++)
                        numbers[j] |= (buf[4 * j + i] & 0xFF) << (8 * (i - 1)); 

}
