CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -I.
LFLAGS=-lboost_system

CMD=$(CXX) $(CXXFLAGS) $(LFLAGS)

all: server client clean

server: server.cpp message.cpp
	$(CMD) server.cpp message.cpp -o server

client: client.cpp message.cpp
	$(CMD) client.cpp message.cpp -o client 

clean:
	rm -f client.o server.o message.o

.PHONY: all clean
