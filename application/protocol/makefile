CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -g -I.
LFLAGS=-lboost_system

CMD=$(CXX) $(CXXFLAGS) $(LFLAGS) $^ -o $@

OBJS = Connection.o Socket.o SocketException.o Message.o Ip.o

all: server client

server: server.o $(OBJS)
	$(CMD)

client: client.o $(OBJS)
	$(CMD)

clean:
	rm -f $(OBJS)

.PHONY: all clean
