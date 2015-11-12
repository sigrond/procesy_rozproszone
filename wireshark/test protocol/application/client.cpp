#include <iostream>
#include <boost/asio.hpp>
#include "message.hpp"

using boost::asio::ip::tcp;

const std::string LOCALHOST = "127.0.0.1";
const int PORT = 5555;
const int BUF_SIZE = 9;

int main()
{
        boost::asio::io_service io_service;

        tcp::socket socket(io_service);
        
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(LOCALHOST), PORT);

        boost::system::error_code error;
        
        socket.connect(endpoint);

        char buffer[9];

        int code = 0;
        int first = 0;
        int second = 0;

        while(code >= 0)
        {
                std::cin>>code>>first>>second;
                
                TestMessage message((TestMessage::Code)code, first, second);
                TestMessage reply(TestMessage::ADD, 0, 0);

                std::cout<<"Sent message:"<<std::endl;
                std::cout<<"   Code: "<<message.code<<std::endl;
                std::cout<<"   Number 1: "<<message.numbers[0]<<std::endl;
                std::cout<<"   Number 2: "<<message.numbers[1]<<std::endl;

                socket.send(boost::asio::buffer(message.send(buffer), BUF_SIZE));

                read(socket, boost::asio::buffer(buffer, BUF_SIZE));
                
                reply.receive(buffer);
                
                std::cout<<"Received reply:"<<std::endl;
                std::cout<<"   Code: "<<reply.code<<std::endl;
                std::cout<<"   Number 1: "<<reply.numbers[0]<<std::endl;
                std::cout<<"   Number 2: "<<reply.numbers[1]<<std::endl;
        }


        return 0;
}
