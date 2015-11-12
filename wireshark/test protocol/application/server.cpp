#include <iostream>
#include <boost/asio.hpp>
#include "message.hpp"

using boost::asio::ip::tcp;

const int PORT = 5555;
const int BUF_SIZE = 9;

int main()
{
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), PORT));

        tcp::socket socket(io_service);

        acceptor.accept(socket);

        char buffer[BUF_SIZE];
                
        boost::system::error_code error;
                
        while(true)
        {
                TestMessage message(TestMessage::ADD, 0, 0);
                TestMessage reply(TestMessage::RESULT, 0, 0);

                read(socket, boost::asio::buffer(buffer, BUF_SIZE));
                
                message.receive(buffer);

                std::cout<<"Received message:"<<std::endl;
                std::cout<<"   Code: "<<message.code<<std::endl;
                std::cout<<"   Number 1: "<<message.numbers[0]<<std::endl;
                std::cout<<"   Number 2: "<<message.numbers[1]<<std::endl;

                switch(message.code)
                {
                        case TestMessage::ADD:
                                reply.numbers[0] = message.numbers[0] + message.numbers[1];
                                break;

                        case TestMessage::SUBTRACT:
                                reply.numbers[0] = message.numbers[0] - message.numbers[1];
                                break;

                        case TestMessage::MULTIPLY:
                                reply.numbers[0] = message.numbers[0] * message.numbers[1];
                                break;

                        case TestMessage::DIVIDE:
                                if(message.numbers[1] == 0)
                                        reply.code = TestMessage::ERROR;
                                else
                                {
                                        reply.numbers[0] = message.numbers[0] / message.numbers[1];
                                        reply.numbers[1] = message.numbers[0] % message.numbers[1];
                                }
                                break;
                        default:
                                reply.code = TestMessage::ERROR;
                }
                               
                reply.send(buffer);

                std::cout<<"Sent reply:"<<std::endl;
                std::cout<<"   Code: "<<reply.code<<std::endl;
                std::cout<<"   Number 1: "<<reply.numbers[0]<<std::endl;
                std::cout<<"   Number 2: "<<reply.numbers[1]<<std::endl;

                socket.send(boost::asio::buffer(buffer, BUF_SIZE));
        }

        return 0;
}
