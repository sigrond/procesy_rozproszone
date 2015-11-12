#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class TestMessage
{
 public:
        enum Code : char 
        {
                ADD = 0, 
                SUBTRACT = 1, 
                MULTIPLY = 2, 
                DIVIDE = 3,
                RESULT = 4,
                ERROR = 5
        };

        TestMessage(Code code, int first, int second);

        ~TestMessage();

        char* send(char* buf);

        void receive(char* buf);

        Code code;
        int numbers[2];
};


#endif // MESSAGE_HPP
